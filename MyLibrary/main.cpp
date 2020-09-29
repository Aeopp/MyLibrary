#include <list>
#include <functional>
#include <iostream>
#include "DELEGATE.h"
#include "singleton_interface.h"
#include "Time.h"

class super
{
private:int i = 0;
public:
	bool foo()
	{
		std::cout << i << std::endl;
		return false; 
	}
};
int main()
{
	Time::instance().initialize();
	super _s;
	
	Time::instance().TimerRegist(1.f, 2.f, 10.f,
		std::bind(&super::foo, &_s));
	
	while(1)
	{
		Time::instance().update();
		
	}
}