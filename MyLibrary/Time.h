#pragma once
#include "singleton_interface.h"
#include <chrono>
#include <functional>
#include <vector>

class Time : public  singleton_interface<Time>
{
public:
	using NotifyEventType = std::function<bool()>;
	// ������ ���� ���� �Է����ּ���.
	void Initialize(const uint32_t LimitFrame);

	bool Update();
	void Render();

	float Delta();
	float TimeScale{ 1.f };
	uint32_t FPS{ 0 };
public:
	// ���� �ð� , �ݺ� �ֱ� , ���� �ð� , �̺�Ʈ
	// ��ȯ�� true �� ���� �ð� ��� ���� �̺�Ʈ ����
	// false �� ��� ����
	void TimerRegist(const float initial, const float Repeat, const float End,
		NotifyEventType _NotifyEvent/*����ǥ���� or std::bind use*/);
public:
	// ��ϵ� �ݹ� �Լ��鿡�� �����ϰ���� Ÿ�ֿ̹� ȣ���Ͽ��ּ���.
	void NotificationCheck()&;
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> PrevTime{};
	std::chrono::duration<float, std::ratio<1, 1000>> SecCheck{};
	std::chrono::duration<float, std::ratio<1, 1000>> LimitDelta{};
	std::chrono::duration<float, std::ratio<1, 1000>> CurrentDelta{};
	std::chrono::steady_clock::time_point CurrentTime{ std::chrono::high_resolution_clock::now() };
	uint32_t _FPSCount{ 0 };
	float DeltaTime{ 0.f };
	// �̺�Ʈ ���ۿ��� , ���� �ð� , �ݺ� �ֱ� , ���� �ð� , ���� ���� �ð�
	std::list<std::tuple<bool, float, float, float, float, NotifyEventType>> _NotifyEvents;
private:
	void RenderFPS()const& noexcept;
};
