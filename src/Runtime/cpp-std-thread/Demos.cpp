#pragma once
#include <iostream>
#include <thread>
namespace Demo00_00
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


namespace Demo01_00
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