#pragma once

#include"IEvent.h"

namespace VIEngine {
	class VI_API IEventAction {
	public:
		virtual ~IEventAction() = default;
		virtual bool Execute(const IEvent* eventObject) = 0;
	};

	template<typename T>
	class VI_API EventAction : public IEventAction {
	public:
		EventAction(const EventCallback<T>& callback) {
			mCallback = callback;
		}
		virtual bool Execute(const IEvent* eventObject) override {
			VI_STATIC_ASSERT(std::is_base_of<IEvent, T>::value && "Execute unkown event");
			return mCallback(*(T*)eventObject);
		}
	private:
		EventCallback<T> mCallback;
	};
}