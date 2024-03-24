#pragma once

#include"EventContext.h"

namespace VIEngine {
	template<typename T> using EventCallback = std::function<bool(const T&)>;

	class VI_API IEventAction {
	public:
		virtual ~IEventAction() = default;
		virtual bool Execute(const EventContext*) = 0;
	};

	template<typename T>
	class VI_API EventAction : public IEventAction {
	public:
		EventAction(const EventCallback<T>& callback) : mCallback(callback) {}
		virtual bool Execute(const EventContext* eventContext) override {
			VI_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Invalid event context");
			return mCallback(*(T*)eventContext);
		}
	private:
		EventCallback<T> mCallback;
	};
}