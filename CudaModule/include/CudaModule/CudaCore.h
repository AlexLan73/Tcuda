#pragma once

#include <memory>
#include <vector>

// Предварительное объявление, чтобы не включать лишнего
namespace nexus { class ScheduledEvent; }

namespace cuda_module {

  // Наш "датчик", который будет генерировать данные
  class TemperatureSensor {
  public:
    void readTemperature(); // Метод, который будет вызываться событием
    float getLastTemperature() const;
  private:
    float m_lastTemp = 0.0f;
  };

  // Промежуточный класс-агрегатор, как ты и просил
  // Пока он просто выводит данные в консоль
  class CudaData {
  public:
    void processData(float temperature);
  };


  // Главный класс модуля
  class CudaCore {
  public:
    CudaCore();
    ~CudaCore();

    // Метод для "подключения" нашего датчика к таймеру из Nexus
//    void linkToEvent(nexus::ScheduledEvent& event);
    void executeSensorPoll();
  private:
    TemperatureSensor m_sensor;
    CudaData m_dataProcessor;
  };

} // namespace cuda_module
