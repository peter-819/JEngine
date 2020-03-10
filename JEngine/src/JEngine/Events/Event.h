#pragma once
#include <JEpch.h>

#include <JEngine/core.h>

namespace JEngine {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	
	enum EventCategory {
		None = 0,
		EventCategoryApplication	 = BIT(0),
		EventCategoryInput			 = BIT(1),
		EventCategoryKeyboard		 = BIT(2),
		EventCategoryMouse			 = BIT(3),
		EventCategoryMouseButton	 = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
								virtual EventType GetEventType() const override { return GetStaticType();} \
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryName() const override { return category; }
	
	class JE_API Event {
		friend class EventDispatcher;
	
	public:																
		virtual EventType GetEventType() const = 0;							//Object's Event Type (Enum)
		virtual const char* GetName() const = 0;							//Object's Event Type (const char*)
		virtual std::string ToString() const { return GetName(); }			//Object's Event Type (String)
																			//GetStaticType()  :  Class's Event Type (Enum)
		virtual int GetCategoryName() const = 0;
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryName() & category;
		}
		bool Handled = false;			//Event Handled
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_Event(event){}
		
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.Handled = func(*(T*)& m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}