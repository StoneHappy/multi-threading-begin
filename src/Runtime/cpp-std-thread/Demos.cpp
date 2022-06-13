#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <future>
#include <string>

namespace Demo00
{
	void DoTask()
	{
		for (size_t i=0; i<300; i++)
		{
			std::cout << "B";
		}

		std::cout << std::endl;
	}

	int main()
	{
		std::thread th(&DoTask);

		for (size_t i = 0; i < 300; i++)
		{
			std::cout << "A";
		}
		
		th.join();

		std::cout << std::endl;

		return 0;
	}
}


namespace Demo01a01
{
	void doTask() {
		std::cout << "Hello from example thread" << std::endl;
	}



	int main() {
		std::thread th(&doTask);

		std::cout << "Hello from main thread" << std::endl;

		th.join();
		return 0;
	}
}

namespace Demo01a02
{

	void doTask(char const* message, int number) {
		std::cout << message << " " << number << std::endl;
	}

	int main() {
		std::thread th(&doTask, "Good day", 19);
		th.join();
		return 0;
	}
}

namespace Demo01b01
{
	class Example {
	public:
		void doTask(const std::string& message)
		{
			std::cout << message << std::endl;
		}
	};

	int main()
	{
		Example example;

		std::thread th(&Example::doTask, &example, "Good day");

		th.join();

		return 0;
	}
}

namespace Demo01b02
{
	class Example {
	public:
		void run() {
			std::thread th(&Example::doTask, this, "Good day");
			th.join();
		}
	private:
		void doTask(const std::string& message)
		{
			std::cout << message << std::endl;
		}
	};

	int main()
	{
		Example example;

		example.run();

		return 0;
	}
}

namespace Demo01b03
{
	class Example {
	public:
		void run() {
			std::thread th(&Example::doTask, "Good day");
			th.join();
		}
	private:
		static void doTask(const std::string& message)
		{
			std::cout << message << std::endl;
		}
	};

	int main()
	{
		Example example;

		example.run();

		return 0;
	}
}

namespace Demo01b04
{
	class Example {
	public:
		void operator()(const std::string& message) {
			std::cout << message << std::endl;
		}
	};

	int main()
	{
		Example example;
		std::thread th(example, "Good day");

		th.join();
		return 0;
	}
}

namespace Demo01c01
{
	int main()
	{
		auto doTask = [](const std::string& message) {
			std::cout << message << std::endl;
		};
		std::thread th(doTask, "Good day");

		th.join();
		return 0;
	}
}

namespace Demo02a01
{
	int main()
	{
		auto doTask = []() {

			for (size_t i = 0; i < 2000000000; i++);
			
			std::cout << "Done!" << std::endl;
		};
		std::thread th(doTask);
		th.join();

		std::cout << "Good bye!" << std::endl;
		return 0;
	}
}

namespace Demo03a01
{
	int main()
	{
		auto doTask = [](std::string& message) {
			std::cout << message << std::endl;
		};

		std::string a = "Good day!";

		std::thread th(doTask, std::ref(a));
		th.join();

		std::cout << "Good bye!" << std::endl;
		return 0;
	}
}

namespace Demo04a01
{
	int main()
	{
		auto doTask = [](const std::string& name) {
			std::cout << name << " is sleeping" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(3));
			std::cout << name << " wakes up" << std::endl;
		};

		std::thread th(doTask, "foo");
		th.join();
		return 0;
	}
}

namespace Demo04a02
{
	using sysclock = std::chrono::system_clock;
	int main()
	{
		auto tpNow = sysclock::now();

		auto tpWakeUpFoo = tpNow + std::chrono::seconds(7);

		std::time_t timeStamp = sysclock::to_time_t(tpWakeUpFoo);
		std::ctime(&timeStamp);

		std::cout << "foo will sleep until " << std::ctime(&timeStamp) << std::endl;

		auto doTask = [](const std::string& name, sysclock::time_point tpWakeUp) {
			std::cout << name << " is sleeping" << std::endl;
			std::this_thread::sleep_until(tpWakeUp);
			std::cout << name << " wakes up" << std::endl;
		};

		std::thread th(doTask, "foo", tpWakeUpFoo);
		th.join();
		return 0;
	}
}

namespace Demo06a01
{
	constexpr int NUM_THREADS = 5;
	int main()
	{

		auto doTask = [](int index) {
			std::cout << index << std::endl;
		};

		std::vector<std::thread> lsThread;

		for (size_t i = 0; i < NUM_THREADS; i++)
		{
			auto th = std::thread(doTask, i);
			lsThread.push_back(std::move(th));
		}

		for (auto&& th : lsThread)
		{
			th.join();
		}
		return 0;
	}
}

namespace Demo07a01
{
	volatile bool isRunning = true;

	int main()
	{

		auto doTask = []() {
			while (isRunning) {
				std::cout << "thread " << " running..." << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}

			std::cout << "thread " << " has been terminated!" << std::endl;
		};
		auto th = std::thread(doTask);
		std::this_thread::sleep_for(std::chrono::seconds(6));
		isRunning = false;
		
		th.join();
		return 0;
	}
}

namespace Demo08a
{

	int main()
	{
		int result[3];
		auto doubleValue = [](int arg, int* res) {
			*res = 2 * arg;
		};

		auto squareValue = [](int arg, int& res) {
			res = arg * arg;
		};

		auto th1 = std::thread(doubleValue, 2, &result[0]);
		auto th2 = std::thread(squareValue, 3, std::ref(result[1]));
		auto th3 = std::thread(doubleValue, 4, &result[2]);

		th1.join();
		th2.join();
		th3.join();

		for (size_t i = 0; i < 3; i++)
		{
			std::cout << result[i] << std::endl;
		}
		return 0;
	}
}


namespace Demo08b
{

	int main()
	{
		auto doubleValue = [](int arg, std::promise<int>& prom) {
			int result = arg * 2;
			std::this_thread::sleep_for(std::chrono::seconds(2));

			prom.set_value(result);

			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "This thread is exiting" << std::endl;
		};
		
		auto prom = std::promise<int>();
		auto fut = prom.get_future();
		auto th1 = std::thread(doubleValue, 2, std::ref(prom));


		int result = fut.get();
		std::cout << result << std::endl;
		th1.join();
		return 0;
	}
}

namespace Demo08c
{
	int main()
	{
		auto doubleValue = [](int arg)->std::string {
			int result = arg * 2;

			std::this_thread::sleep_for(std::chrono::seconds(2));
			return std::to_string(result);
		};

		auto ptask = std::packaged_task<std::string(int)>(doubleValue);
		auto fut = ptask.get_future();

		auto th1 = std::thread(std::move(ptask), 2);


		std::string result = fut.get();
		std::cout << result << std::endl;
		th1.join();
		return 0;
	}
}

namespace Demo09
{
	int main()
	{
		auto foo = [](){
			std::cout << "foo is starting ..." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "foo is exiting ..." << std::endl;
		};

		auto th1 = std::thread(foo);

		th1.detach();

		std::this_thread::sleep_for(std::chrono::seconds(3));

		std::cout << "Main thread is exiting" << std::endl;
		return 0;
	}
}