#include "pch.h"

#include "CudaModule/CudaCore.h"
#include "Nexus/ScheduledEvent.h" // Включаем, т.к. используем в методе
#include <iostream>
#include <random>
#include <nvml.h>


namespace cuda_module {


  // --- TemperatureSensor ---
  void TemperatureSensor::readTemperature() {
    // Пока что генерируем случайную температуру
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(35.0, 95.0);
    m_lastTemp = static_cast<float>(distr(gen));

    nvmlReturn_t result;
    result = nvmlInit();
    if (NVML_SUCCESS != result) {
      std::cerr << "Failed to initialize NVML: " << nvmlErrorString(result) << std::endl;
      return ;
    }

    nvmlDevice_t device;
    result = nvmlDeviceGetHandleByIndex(0, &device); // 0 — индекс GPU
    if (NVML_SUCCESS != result) {
      std::cerr << "Failed to get handle for device 0: " << nvmlErrorString(result) << std::endl;
      nvmlShutdown();
      return ;
    }

    unsigned int temp;
    result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
    if (NVML_SUCCESS != result) {
      std::cerr << "Failed to get temperature: " << nvmlErrorString(result) << std::endl;
    }
    else {
      std::cout << "GPU Temperature: " << temp << " C" << std::endl;
    }

    nvmlShutdown();

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

