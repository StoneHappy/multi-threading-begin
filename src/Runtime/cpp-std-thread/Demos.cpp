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