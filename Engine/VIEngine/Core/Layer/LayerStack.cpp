#include"LayerStack.h"

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(LayerStack)

	LayerStack::LayerStack() : mIndex(0), mLayers() {

	}

	LayerStack::~LayerStack() {

	}

	void LayerStack::Push(Layer* layer) {
		mLayers.emplace(mLayers.begin() + mIndex, layer);
		mIndex++;
	}

	void LayerStack::PushOverlay(Layer* layer) {
		mLayers.emplace_back(layer);
	}

	void LayerStack::Pop(Layer* layer) {
		auto iter = std::find(mLayers.begin(), mLayers.end(), layer);
		if (iter != mLayers.end()) {
			mLayers.erase(iter);
			mIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer) {
		auto iter = std::find(mLayers.begin(), mLayers.end(), layer);
		if (iter != mLayers.end()) {
			mLayers.erase(iter);
		}
	}
}