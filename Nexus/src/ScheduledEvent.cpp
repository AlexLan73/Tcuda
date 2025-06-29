#include "pch.h"
#include "Nexus/ScheduledEvent.h"


namespace nexus {

  ScheduledEvent::ScheduledEvent(std::function<void()> eventCallback)
    : m_ioContext(), m_timer(m_ioContext), m_eventCallback(std::move(eventCallback)) {
  }

  ScheduledEvent::~ScheduledEvent() {
    stop();
  }

  void ScheduledEvent::start(int intervalMs) {
    if (m_thread.joinable()) { // Если уже запущен, не делать ничего
      return;
    }
    m_isStopped = false;
    m_interval = std::chrono::milliseconds(intervalMs);
    m_timer.expires_at(std::chrono::steady_clock::now() + m_interval);
    m_timer.async_wait([this](const boost::system::error_code& ec) {
      if (!ec) scheduleNext();
      });

    // Запускаем io_context в отдельном потоке, чтобы не блокировать основной
    m_thread = std::thread([this]() { m_ioContext.run(); });
  }

  void ScheduledEvent::stop() {
    if (m_isStopped) return;
    m_isStopped = true;
    m_ioContext.stop();
    if (m_thread.joinable()) {
      m_thread.join();
    }
  }

  void ScheduledEvent::pause() {
    m_isPaused = true;
  }

  void ScheduledEvent::resume() {
    m_isPaused = false;
  }

  void ScheduledEvent::scheduleNext() {
    if (m_isStopped) return;

    if (!m_isPaused) {
      // Выполняем наше событие!
      m_eventCallback();
    }

    // Планируем следующий вызов
    m_timer.expires_at(m_timer.expiry() + m_interval);
    m_timer.async_wait([this](const boost::system::error_code& ec) {
      if (!ec) scheduleNext();
      });
  }

} // namespace nexus

