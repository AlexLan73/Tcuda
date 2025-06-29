#include "pch.h"

#include "CudaModule/CudaCore.h"
#include "Nexus/ScheduledEvent.h" // Включаем, т.к. используем в методе
#include <iostream>
#include <random>

namespace cuda_module {


  // --- TemperatureSensor ---
  void TemperatureSensor::readTemperature() {
    // Пока что генерируем случайную температуру
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(35.0, 95.0);
    m_lastTemp = static_cast<float>(distr(gen));
  }

  float TemperatureSensor::getLastTemperature() const {
    return m_lastTemp;
  }

  // --- CudaData ---
  void CudaData::processData(float temperature) {
    // В будущем здесь будет отправка в MemoryData
    // А сейчас - просто выводим на консоль
    std::cout << "[CudaData]: Received new temperature: " << temperature << " C" << std::endl;
  }

  // --- CudaCore ---
  CudaCore::CudaCore() {}
  CudaCore::~CudaCore() {}

  void CudaCore::executeSensorPoll() {
    // 1. Датчик считывает данные
    m_sensor.readTemperature();
    // 2. Агрегатор их обрабатывает (выводит в консоль)
    m_dataProcessor.processData(m_sensor.getLastTemperature());
  }

} // namespace cuda_module

