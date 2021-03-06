#include "InputManager.h"


void InputManager::Update() & noexcept
{
	for (typename InputManager::VirtualTableKeyDataType CurrentVirtualKey =
		0x01; CurrentVirtualKey <= 0xFE; ++CurrentVirtualKey)
	{
		if (!EventRegistCheckTable[CurrentVirtualKey]) continue;

		auto& [CurrentKeyState, EventList] = _ActionTable[CurrentVirtualKey];

		bool  bCurrentTableState= (GetAsyncKeyState(CurrentVirtualKey) & 0x8000);

		 // 현재 호출시점 눌린 상태
		 if (bCurrentTableState)
		 {
			 switch (CurrentKeyState)
			 {
			 case InputManager::EKEY_STATE::DOWN:
				 CurrentKeyState = InputManager::EKEY_STATE::PRESSING;
				 break;
			 case InputManager::EKEY_STATE::PRESSING:
				 break;
			 case InputManager::EKEY_STATE::UP:
				 CurrentKeyState = InputManager::EKEY_STATE::DOWN;
				 break;
			 case InputManager::EKEY_STATE::NONE:
				 CurrentKeyState = InputManager::EKEY_STATE::DOWN;
				 break; 
			 default:
				 break;
			 }
		 }
		 else
		 {
			 switch (CurrentKeyState)
			 {
			 case InputManager::EKEY_STATE::DOWN:
				 CurrentKeyState = InputManager::EKEY_STATE::UP;
				 break;
			 case InputManager::EKEY_STATE::PRESSING:
				 CurrentKeyState = InputManager::EKEY_STATE::UP;
				 break;
			 case InputManager::EKEY_STATE::UP:
				 CurrentKeyState = InputManager::EKEY_STATE::NONE;
				 break;
			 case InputManager::EKEY_STATE::NONE:
				 break;
			 default:
				 break;
			 }
		 }

		 if(CurrentKeyState!= InputManager::EKEY_STATE::NONE)
			 EventList[std::underlying_type_t<std::decay_t<decltype(CurrentKeyState)>>(CurrentKeyState)].BroadCast();
	}
}

std::shared_ptr<typename InputManager::DelegateType::MyHandleType>
				InputManager::EventRegist
								(typename DelegateType::EventType NotifyEvent,
								typename InputManager::VirtualTableKeyDataType VKKey, 
								typename InputManager::EKEY_STATE _KeyState) & noexcept
{
	_ActionTable[VKKey].first = InputManager::EKEY_STATE::NONE;
	// 해당 키는 이벤트 가 등록됨
	EventRegistCheckTable[VKKey] = true;
	return _ActionTable[VKKey].second[std::underlying_type_t<decltype(_KeyState)>(_KeyState)] += NotifyEvent;

}
