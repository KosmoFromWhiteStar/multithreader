#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <ctime>
#include <iomanip>


std::vector <std::string> win_list;
std::mutex list_access;

void way (int speed, std::string name)
{
	double dis = 0.f;
	std::time_t timer = std::time(nullptr);
	std::time_t now = timer;

	do {
		if (std::difftime(timer, now) == 1)
		{
			dis += speed;
			std::cout << "----------------\n";
			std::cout << name << " dis " << dis << std::endl;
			now = std::time(nullptr);
		}
		timer = std::time(nullptr);
	} while (dis <= 100);

	list_access.lock();
	win_list.push_back(name);
	std::cout << win_list.back() << " is finished\n";
	list_access.unlock();
}

int main()
{
	
	std::vector<int> speed(6);
	std::vector<std::string> name(6);

	for (int i = 0; i < 6; i++)
	{
		std::cin >> speed[i];
		std::cin >> name[i];
	}
	std::thread	way1(way, speed[0], name[0]);
	std::thread	way2(way, speed[1], name[1]);
	std::thread	way3(way, speed[2], name[2]);
	std::thread	way4(way, speed[3], name[3]);
	std::thread	way5(way, speed[4], name[4]);
	std::thread	way6(way, speed[5], name[5]);

	if (way1.joinable()) way1.join();
	if (way2.joinable()) way2.join();
	if (way3.joinable()) way3.join();
	if (way4.joinable()) way4.join();
	if (way5.joinable()) way5.join();
	if (way6.joinable()) way6.join();
	 
	std::cout << "===============|Winers|==========\n";
	for (int i = 0; i < 6; i++)
	{
		std::cout << i << " " << win_list[i] << std::endl;
	}
	
}