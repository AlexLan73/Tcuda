#pragma once

#define _WIN32_WINNT 0x0A00  // Windows 10+

#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include <chrono>
#include <functional>
#include <thread>
#include "MemoryData/SharedDataTypes.h"

namespace nexus {

  class ScheduledEvent {
  public:
    // Конструктор принимает функцию, которую нужно вызывать (наше "событие")
    explicit ScheduledEvent(std::function<void()> eventCallback);
    ~ScheduledEvent();

    // Запускает таймер с заданным интервалом в миллисекундах
    void start(int intervalMs);

    // Полностью останавливает таймер и поток
    void stop();

    // Приостанавливает вызов события, но таймер продолжает "тикать"
    void pause();

    // Возобновляет вызов события
    void resume();

  private:
    void scheduleNext();

    boost::asio::io_context m_ioContext;
    boost::asio::steady_timer m_timer;
    std::function<void()> m_eventCallback;
    std::chrono::milliseconds m_interval;
    std::thread m_thread;
    bool m_isPaused = false;
    bool m_isStopped = false;

  };

} // namespace nexus
