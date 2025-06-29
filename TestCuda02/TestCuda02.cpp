// TestCuda02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

#include <fcntl.h>
#include <any>
#include <nvml.h>



int main()
{
    std::cout << "Hello World!\n";

    const double pi = 3.14159265358979323846;


    nvmlReturn_t result;
    result = nvmlInit();
    if (NVML_SUCCESS != result) {
      std::cerr << "Failed to initialize NVML: " << nvmlErrorString(result) << std::endl;
      return 1;
    }

    nvmlDevice_t device;
    result = nvmlDeviceGetHandleByIndex(0, &device); // 0 — индекс GPU
    if (NVML_SUCCESS != result) {
      std::cerr << "Failed to get handle for device 0: " << nvmlErrorString(result) << std::endl;
      nvmlShutdown();
      return 1;
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
