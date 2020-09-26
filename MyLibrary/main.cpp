#include <list>
#include <functional>
#include <iostream>
#include "DELEGATE.h"

// 멤버 함수
// 전역 함수
// 정적 멤버 함수
// 삭제해보기
namespace global
{
	float  function()
	{
		std::cout << __FUNCTION__ << std::endl;
		return 1;
	}
}
class _Class
{

public:
	_Class()
	{
		static int32_t uid = 0;
		id = uid++;
	}
	int32_t id = 0;
	void foo()
	{
		
		std::cout << id << std::endl;
		
	}
	static int bar(float&b, float w)
	{
		
		std::cout << __FUNCTION__<< std::endl;
		return 1;
	}
};
int main()
{
	_Class A;
	_Class B;

	Delegate<void()> _Delegate;

	auto h1 = _Delegate += std::bind(&_Class::foo, &A);
	auto h2 = _Delegate += std::bind(&_Class::foo, &B);

	_Delegate.Clear();
	
	_Delegate.BroadCast();

	_Delegate -= (h1);
	

	_Delegate.BroadCast();
	
}