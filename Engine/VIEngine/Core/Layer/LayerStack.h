#pragma once

#include"Layer.h"

namespace VIEngine {
    using LayerList = std::vector<Layer*>;
    using LayerListIterator = std::vector<Layer*>::iterator;
    using LayerListReversedIterator = std::vector<Layer*>::reverse_iterator;

    class VI_API LayerStack {
    public:
        class VI_API ReverseIterator {
        public:
            ReverseIterator() = default;
            explicit ReverseIterator(LayerListReversedIterator iter) : mCurrentIter(iter) {
               
            }

            ReverseIterator& operator++() {
                ++mCurrentIter;
                return *this;
            }

            ReverseIterator& operator--() {
                --mCurrentIter;
                return *this;
            }

            bool operator!=(const ReverseIterator& other) const {
                return mCurrentIter != other.mCurrentIter;
            }

            Layer* operator*() const {
                return *mCurrentIter;
            }

            Layer* operator->() const {
                return *mCurrentIter;
            }

        private:
            LayerListReversedIterator mCurrentIter;
        };

        LayerStack() : mLayers(), mIndex(0) {}
        ~LayerStack() {
            mLayers.clear();
        }

        void PushLayer(Layer* layer) {
            mLayers.emplace(mLayers.begin() + mIndex, layer);
            mIndex++;
        }

        void PopLayer(Layer* layer) {
            auto iter = std::find(mLayers.begin(), mLayers.end(), layer);
            if (iter != mLayers.end()) {
                mLayers.erase(iter);
                mIndex--;
            }
        }

        void PushOverlay(Layer* layer) {
            mLayers.emplace_back(layer);
        }

        void PopOverlay(Layer* layer) {
            auto iter = std::find(mLayers.begin(), mLayers.end(), layer);
            if (iter != mLayers.end()) {
                mLayers.erase(iter);
            }
        }

        void Free() {
            for (auto iter : mLayers) {
                VI_FREE_MEMORY(iter);
            }
            mLayers.clear();
        }

        LayerListIterator begin() { return mLayers.begin(); }
        LayerListIterator end() { return mLayers.end(); }

        ReverseIterator rbegin() { return ReverseIterator(mLayers.rbegin()); }
        ReverseIterator rend() { return ReverseIterator(mLayers.rend()); }
    private:
        LayerList mLayers;
        uint8_t mIndex;
    };
}