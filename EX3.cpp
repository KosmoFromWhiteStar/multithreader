#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


std::vector <int> order_list;
std::mutex order_list_access;


enum FOOD
{
	pizza,
	sup,
	steak,
	salad,
	susi,
};

std::string r_food(int food)
{
	if (food == FOOD::pizza) return "pizza";
	if (food == FOOD::sup)   return "sup";
	if (food == FOOD::steak) return "steak";
	if (food == FOOD::salad) return "salad";
	if (food == FOOD::susi)  return "susi";
}

void order_func()
{
	std::srand(std::time(nullptr));
	int sec = std::rand() % 10 + 5;
	std::this_thread::sleep_for(std::chrono::seconds(sec));
	int food = std::rand() % 5;
	std::cout << "Order on " << r_food(food) << std::endl;
	order_list_access.lock();
	order_list.push_back(food);
	order_list_access.unlock();
}

void cooking()
{
	int sec = std::rand() % 15 + 5;
	std::this_thread::sleep_for(std::chrono::seconds(sec));
	order_list_access.lock();
	std::cout << order_list.back() << " cooking\n";
	order_list_access.unlock();
}

void deliver()
{
	std::this_thread::sleep_for(std::chrono::seconds(30));
	std::cout << "delivered\n";
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		std::thread oreder(order_func);
		std::thread cook(cooking);
		std::thread cur(deliver);
		oreder.join();
		cook.join();
		cur.join();
	}
	order_list_access.lock();
	for (int i = 0; i < order_list.size(); i++)
	{
		std::cout << r_food(order_list[i]) << std::endl;
	}
	order_list_access.unlock();
}