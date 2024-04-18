#include"ThreadPool.h"

namespace VIEngine {
	ThreadPool::ThreadPool(size_t numThreads) : mStop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            mWorkers.emplace_back([this] {
                while (true) {
                    std::unique_lock<std::mutex> lock(mQueueMutex);
                    mCondition.wait(lock, [this] { return mStop  || !mJobs.empty(); });

                    if (mStop && mJobs.empty()) return;

                    mJobs.front()();
                    mJobs.pop();
                }
            });
        }
	}

	ThreadPool::~ThreadPool() {
	}

    void ThreadPool::JoinAndRelease() {
        {
            std::unique_lock<std::mutex> lock(mQueueMutex);
            mStop = true;
        }
        mCondition.notify_all();
        for (std::thread& worker : mWorkers) {
            worker.join();
        }
    }
}