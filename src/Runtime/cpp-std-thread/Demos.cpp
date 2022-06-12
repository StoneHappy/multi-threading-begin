#pragma once
#include <iostream>
#include <thread>
namespace Demo001
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