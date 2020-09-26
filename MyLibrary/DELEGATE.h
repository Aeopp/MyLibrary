#include <functional>
#include <vector>
#include <map>

using namespace std::placeholders;

template<class T>class Delegate;

template<typename ReturnType, typename... ParamTypes>
class Delegate<ReturnType(ParamTypes...)>
{
public:
	using Event_ID = int32_t; 
	using EventType = std::function<ReturnType(ParamTypes...)>;
private:
	std::map< Event_ID, EventType > EventList;
public:
	// 람다 or Bind(placeholder) 를 사용해주세요.
	[[nodiscard]] Event_ID operator +=(EventType _EventRegist)
	{
		static Event_ID _ID{ 0 };
		
		EventList.insert(std::make_pair(++_ID, std::move(_EventRegist)));
		return _ID;
	}
	size_t operator-=(const Event_ID _DeleteEventID)
	{
		return EventList.erase(_DeleteEventID);
	}
	[[nodiscard]] std::vector<ReturnType> BroadCast(ParamTypes&&... Params)
	{
		std::vector<ReturnType> _ReturnVals;
		_ReturnVals.reserve(EventList.size());
		
		for (auto& [ID,NotifyEvent]: EventList)
		{
			if (NotifyEvent)
				_ReturnVals.push_back(NotifyEvent(std::forward<ParamTypes>(Params)...));
		}
		return _ReturnVals;
	}
	void Clear()
	{
		EventList.clear();
	}
};

template<typename... ParamTypes>
class Delegate<void(ParamTypes...)>
{
public:
	using Event_ID = int32_t;
	using EventType = std::function<void(ParamTypes...)>;
private:
	std::map< Event_ID, EventType > EventList;
public:
	// 람다 or Bind(placeholder) 를 사용해주세요.
	[[nodiscard]] Event_ID operator +=(EventType _EventRegist)
	{
		static Event_ID _ID{ 0 };

		EventList.insert(std::make_pair(++_ID, std::move(_EventRegist)));
		return _ID;
	}
	size_t operator-=(const Event_ID _DeleteEventID)
	{
		return EventList.erase(_DeleteEventID);
	}
	void BroadCast(ParamTypes&&... Params)
	{
		for (auto& [ID,NotifyEvent]: EventList)
		{
			if (NotifyEvent)
				NotifyEvent(std::forward<ParamTypes>(Params)...);
		}
	}
	void Clear()
	{
		EventList.clear();
	}
};