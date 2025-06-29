// TcudaApp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

// main.cpp
#include "Nexus/ScheduledEvent.h"
#include "CudaModule/CudaCore.h"
#include <iostream>
#include <string>

void application_main_loop() {
  std::cout << "Application is running. Press Enter to stop..." << std::endl;
  std::string line;
  std::getline(std::cin, line);
}

int main() {
  std::cout << "Initializing system..." << std::endl;

  // 1. Создаем ядро нашего Cuda-модуля
  cuda_module::CudaCore cudaCore;

  // 2. Создаем управляемое событие, передавая ему в конструктор
  //    лямбда-функцию, которая вызывает публичный метод CudaCore.
  //    Захватываем cudaCore по ссылке [&].
  nexus::ScheduledEvent tempEvent([&cudaCore]() {
    cudaCore.executeSensorPoll();
    });

  // 3. Просто запускаем событие с нужным интервалом.
  //    Теперь вызов start правильный - он принимает только один аргумент.
  tempEvent.start(1000);

  std::cout << "System started. Temperature readings will appear every second." << std::endl;

  application_main_loop();

  std::cout << "Shutting down..." << std::endl;
  tempEvent.stop();

  std::cout << "System stopped." << std::endl;

  return 0;
}
