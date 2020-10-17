#include "Time.h"
#include <iostream>
void Time::Initialize(const uint32_t LimitFrame)
{
	using namespace std::chrono_literals;

	PrevTime = std::chrono::high_resolution_clock::now();
	LimitDelta = 1000ms / (float)LimitFrame;
}

bool Time::Update()
{
	using namespace std::chrono_literals;

	std::chrono::time_point CurrentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::ratio<1, 1000>> Delta = CurrentTime - PrevTime;

	if (LimitDelta > Delta)
		return false;

	SecCheck += Delta;

	if (SecCheck >= 1000ms)
	{
		FPS = _FPSCount;
		_FPSCount = 0;
		SecCheck = 0ms;
	}
	else
		++_FPSCount;

	PrevTime = CurrentTime;

	DeltaTime = (Delta.count() * 0.001f) * TimeScale;

	return true;
}

void Time::Render()
{
	RenderFPS();
}

float Time::Delta()
{
	return DeltaTime;
}

void Time::TimerRegist(const float initial, const float Repeat, const float End,
	NotifyEventType _NotifyEvent)
{
	_NotifyEvents.emplace_back(false, initial, Repeat, End, initial, std::move(_NotifyEvent));
}

void Time::NotificationCheck()&
{
	// 시작 시간 , 반복 주기 , 종료 시간 , 현재 측정 시간
	for (auto iter = std::begin(_NotifyEvents);
		iter != std::end(_NotifyEvents);)
	{
		auto& [bInit, Init, Repeat, End, CurrentDelta, Event] = *iter;

		Init -= DeltaTime;
		if (Init > 0.f)continue;

		if (Init < 0.f && !bInit)
		{
			bInit = true;
			CurrentDelta = -0.1f;
		}

		CurrentDelta -= DeltaTime;
		End -= DeltaTime;
		bool IsNotifyEnd = false;

		if (CurrentDelta < 0.f)
		{
			IsNotifyEnd |= Event();
			CurrentDelta = Repeat;
		}

		IsNotifyEnd |= (End < 0.f);

		if (IsNotifyEnd)
		{
			iter = _NotifyEvents.erase(iter);
			continue;
		}

		++iter;
	}
}

void Time::RenderFPS() const& noexcept
{
	
}
