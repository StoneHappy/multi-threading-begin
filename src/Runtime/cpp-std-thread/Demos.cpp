#pragma once
#include <iostream>
#include <thread>
using namespace std;
namespace Demo001
{
	void doTask() {
		for (int i = 0; i < 300; ++i)
			cout << "B";

		cout << endl;
	}
	int main() {
		std::thread th(&doTask);

		for (int i = 0; i < 300; ++i)
			cout << "A";

		th.join();

		cout << endl;
		return 0;
	}
}