#pragma once
#include "singleton_interface.h"
#include <chrono>
#include <functional>
#include <vector>

class Time  : public  singleton_interface<Time>
{
public:
	using NotifyEventType = std::function<bool()>;
	void initialize();
	void update();

	float Delta();
	float TimeScale{ 1.f };
	uint32_t FPS{0};
public:
	// 시작 시간 , 반복 주기 , 종료 시간 , 이벤트
	// 반환값 true 시 종료 시간 상관 없이 이벤트 삭제
	// false 시 계속 유지
	void TimerRegist(const float initial, const float Repeat, const float End,
		NotifyEventType _NotifyEvent/*람다표현식 or std::bind use*/);
private:
	void NotificationCheck()&;
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> PrevTime{};
	std::chrono::duration<float, std::ratio<1, 1000>> SecCheck{};
	uint32_t _FPSCount{ 0 };
	float DeltaTime{ 0.f };
	// 이벤트 시작여부 , 시작 시간 , 반복 주기 , 종료 시간 , 현재 측정 시간
	std::list<std::tuple<bool,float, float, float, float, NotifyEventType>> _NotifyEvents;
};

