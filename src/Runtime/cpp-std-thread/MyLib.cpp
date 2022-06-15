#include "MyLib.h"
#include <iostream>
namespace MyLib
{

	ExecService::ExecService(int numThreads)
	{
		init(numThreads);
	}

	void ExecService::submit(taskFunc task)
	{
		{
			uniquelk lk(m_MutexTaskPending);
			m_TaskPending.push(task);
		}

		m_ConTaskPending.notify_one();
	}

	void ExecService::waitTaskDone()
	{
		for (;;)
		{
			uniquelk lkPending(m_MutexTaskPending);

			if (m_TaskPending.empty())
			{
				uniquelk lkRunning(m_MutexTaskRunning);

				m_ConTaskRunning.wait(lkRunning);

				break;
			}
		}
	}

	void ExecService::shutdown()
	{
		{
			uniquelk lk(m_MutexTaskPending);
			m_ForceThreadShutdown = true;
			std::queue<taskFunc>().swap(m_TaskPending);
		}

		m_ConTaskPending.notify_all();

		for (auto&& th : m_ListThread)
		{
			th.join();
		}

		m_NumThread = 0;
		m_ListThread.clear();
	}

	void ExecService::init(int numThreads)
	{
		m_NumThread = numThreads;
		m_ListThread.resize(numThreads);

		for (auto&& th : m_ListThread)
		{
			th = std::thread(&threadWorkerFunc, this);
		}
	}

	void ExecService::threadWorkerFunc(ExecService* thisPtr)
	{
		auto&& mutexTaskPending = thisPtr->m_MutexTaskPending;
		auto&& conTaskPending = thisPtr->m_ConTaskPending;
		auto&& conTaskRunning = thisPtr->m_ConTaskRunning;
		auto&& forceThreadShutdown = thisPtr->m_ForceThreadShutdown;
		auto&& taskPending = thisPtr->m_TaskPending;
		taskFunc task = nullptr;
		for (;;) {
			{
				uniquelk lkPending(mutexTaskPending);
				std::cout << "waiting..." << std::endl;
				conTaskPending.wait(lkPending, [&] {
					return forceThreadShutdown || !taskPending.empty();
					});
				
				if (forceThreadShutdown)
				{
					break;
				}

				task = taskPending.front();
				taskPending.pop();
			}
			std::cout << "task doing..." << std::endl;
			task();

			conTaskRunning.notify_one();
		}
	}

}