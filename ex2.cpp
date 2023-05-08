#include <iostream>
#include <thread>
#include <mutex>


std::mutex list_access;

void rain_station(int sec, std::string name)
{
	std::this_thread::sleep_for(std::chrono::seconds(sec));
	list_access.lock();
	std::string depart;
	std::cout << name << " on station\n";
	std::cin >> depart;
	if (depart == "depart") std::cout << name << " departed\n";
	list_access.unlock();
}


int main()
{
	int sec[3];
	std::cin >> sec[0] >> sec[1] >> sec[2];

	std::thread train_A(rain_station, sec[0], "Train A");
	std::thread train_B(rain_station, sec[1], "Train B");
	std::thread train_C(rain_station, sec[2], "Train C");
	train_A.join();
	train_B.join();
	train_C.join();
}