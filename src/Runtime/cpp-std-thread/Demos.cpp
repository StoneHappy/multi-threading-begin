#pragma once
#include <iostream>
#include <thread>
#include <chrono>

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