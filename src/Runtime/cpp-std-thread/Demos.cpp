#pragma once
#include <iostream>
#include <thread>
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