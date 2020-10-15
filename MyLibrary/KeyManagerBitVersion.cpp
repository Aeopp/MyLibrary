// Type your code here, or load an example.

#include <utility>
#include <Windows.h>
#include <bitset>
#include "DELEGATE.h"
#include <thread>
#include <chrono>
#include <iostream>



#include <iostream>
#include "InputManager.h"

static auto press = []() {
	std::cout << "눌림" << std::endl; 
	
};

static auto up = []()  {
	std::cout << "업" << std::endl;
	
};
static auto down = []() {
	std::cout << "다운" << std::endl;
	
};

int main()
{
	InputManager d;
auto hd = d.EventRegist(down, VK_SPACE, InputManager::EKEY_STATE::DOWN);
	auto hu = d.EventRegist(up, VK_SPACE, InputManager::EKEY_STATE::UP);
	auto hp = d.EventRegist(press, VK_SPACE, InputManager::EKEY_STATE::PRESSING);
	int i = 0;
	while (true)
	{
		d.Update();
		++i;
		/*if (i == 2)
		{
			hd.Invalidate();
		}
		if (i == 3)
		{
			hu.Invalidate();

		}*/
		if (i == 100)
		{
			hu.Invalidate();
		}
	}
	/*InputManager _InputManager;
	_InputManager.EventRegist(press, VK_SPACE, InputManager::EKEY_STATE::PRESSING);
	_InputManager.EventRegist(up, VK_SPACE, InputManager::EKEY_STATE::UP);
	_InputManager.EventRegist(down, VK_SPACE, InputManager::EKEY_STATE::DOWN);

	while (true)
	{
		_InputManager.Update();

	}*/
	
	/*while (1)
	{
		_KeyManager.Key_Update();

		if (_KeyManager.Key_Down(VK_RBUTTON))
		{
			std::cout << "DOWN LEFT" << std::endl;
		}
		if (_KeyManager.Key_Pressing(VK_RBUTTON))
		{
			std::cout << "PRESS LEFT" << std::endl;
		}
		if (_KeyManager.Key_Up(VK_RBUTTON))
		{
			std::cout << "UP LEFT" << std::endl;
		}
	};*/
};