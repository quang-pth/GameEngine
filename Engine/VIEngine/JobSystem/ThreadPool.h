#pragma once

#include"pch.h"
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>

namespace VIEngine {
	using ThreadJob = std::function<void()>;

	class ThreadPool {
	public:
		ThreadPool(size_t numThreads);
		~ThreadPool();

		template<typename F, typename... Args>
		void SubmitJob(const F& f, Args&&... args) {
			{
				std::unique_lock<std::mutex> lock(mQueueMutex);
				mJobs.emplace([=]() { std::invoke(f, args...); });
			}
			mCondition.notify_one();
		}

		void JoinAndRelease();
	private:
		std::vector<std::thread> mWorkers;
		std::queue<ThreadJob> mJobs;
		std::mutex mQueueMutex;
		std::condition_variable mCondition;
		bool mStop;
	};
}