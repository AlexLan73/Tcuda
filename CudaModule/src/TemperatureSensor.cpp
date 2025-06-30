#include "pch.h"
#include "CudaModule/TemperatureSensor.h"

#include <iostream>
#include <ostream>
#include <random>



namespace cuda_module {
	TemperatureSensor::TemperatureSensor()
	{
    //result_ = nvmlInit();
    //if (NVML_SUCCESS != result_) {
    //  std::cerr << "Failed to initialize NVML: " << nvmlErrorString(result_) << std::endl;
    //  return;
    //}

    //
    //result_ = nvmlDeviceGetHandleByIndex(0, &device_); // 0 Ч индекс GPU
    //if (NVML_SUCCESS != result_) {
    //  std::cerr << "Failed to get handle for device 0: " << nvmlErrorString(result_) << std::endl;
    //  nvmlShutdown();
    //  return;
    //}

    //result_ = nvmlDeviceGetTemperature(device_ NVML_TEMPERATURE_GPU, &temp_);
    //if (NVML_SUCCESS != result_) {
    //  std::cerr << "Failed to get temperature: " << nvmlErrorString(result_) << std::endl;
    //}
    //else {
    //  std::cout << "GPU Temperature: " << temp_ << " C" << std::endl;
    //}

    //nvmlShutdown();

	}

	// --- TemperatureSensor ---
  void TemperatureSensor::readTemperature() {
		//nvmlReturn_t result;
  //      result = nvmlInit();
  //      if (NVML_SUCCESS != result) {
  //          std::cerr << "Failed to initialize NVML: " << nvmlErrorString(result) << std::endl;
  //          return ;
  //      }

  //      nvmlDevice_t device;
  //      result = nvmlDeviceGetHandleByIndex(0, &device); // 0 Ч индекс GPU
  //      if (NVML_SUCCESS != result) {
  //          std::cerr << "Failed to get handle for device 0: " << nvmlErrorString(result) << std::endl;
  //          nvmlShutdown();
  //          return ;
  //      }

  //      unsigned int temp;
  //      result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);
  //      if (NVML_SUCCESS != result) {
  //          std::cerr << "Failed to get temperature: " << nvmlErrorString(result) << std::endl;
  //      }
  //      else {
  //          std::cout << "GPU Temperature: " << temp << " C" << std::endl;
  //      }

  //      nvmlShutdown();



      // ѕока что генерируем случайную температуру
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distr(35.0, 95.0);
        m_lastTemp = static_cast<float>(distr(gen));

        //result_ = nvmlDeviceGetTemperature(device_ NVML_TEMPERATURE_GPU, &temp_);
        //if (NVML_SUCCESS != result_) {
        //  std::cerr << "Failed to get temperature: " << nvmlErrorString(result_) << std::endl;
        //}
        //else {
        //  std::cout << "GPU Temperature: " << temp_ << " C" << std::endl;
        //}
        //m_lastTemp = static_cast<float>(result_);

    }

    float TemperatureSensor::getLastTemperature() const {
        return m_lastTemp;
    }
}
