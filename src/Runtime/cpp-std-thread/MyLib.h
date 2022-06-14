#pragma once
#include <functional>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <condition_variable>

namespace MyLib
{
	class ExecService {
	public:
		using taskFunc = std::function<void()>;
		using uniquelk = std::unique_lock<std::mutex>;

		ExecService(int numThreads);

		void submit(taskFunc task);
		void waitTaskDone();
		void shutdown();
				

	private:
		void init(int numThreads);
		static void threadWorkerFunc(ExecService* thisPtr);
		std::vector<std::thread> m_ListThread;
		std::queue<taskFunc> m_TaskPending;
		std::condition_variable m_ConTaskPending;
		std::condition_variable m_ConTaskRunning;
		std::mutex m_MutexTaskPending;

		int m_NumThread;
		bool m_ForceThreadShutdown = false;
	};
}