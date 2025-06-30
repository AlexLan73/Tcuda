#pragma once


#include <nvml.h>
namespace nexus { class ScheduledEvent; }



namespace cuda_module {
	// ��� "������", ������� ����� ������������ ������
  class TemperatureSensor {
  public:
		TemperatureSensor();
    void readTemperature(); // �����, ������� ����� ���������� ��������
    float getLastTemperature() const;
  private:
		float m_lastTemp = 0.0f;
//    nvmlReturn_t result_;
//    nvmlDevice_t device_;
//    unsigned int temp_;


  };
}