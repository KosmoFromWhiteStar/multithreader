#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


std::vector <int> order_list;


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
	std::mutex meals_mtx;
	std::srand(std::time(nullptr));
	int sec = std::rand() % 10 + 5;
	std::this_thread::sleep_for(std::chrono::seconds(sec));
	int food = std::rand() % 5;
	std::cout << "Order on " << r_food(food) << std::endl;
	meals_mtx.lock();
	order_list.push_back(food);
	meals_mtx.unlock();
}

void cooking()
{
	std::mutex cooking_mtx;
	int sec = std::rand() % 15 + 5;
	std::this_thread::sleep_for(std::chrono::seconds(sec));
	cooking_mtx.lock();
	std::cout << r_food(order_list.back()) << " cooking\n";
	cooking_mtx.unlock();
}

void deliver()
{
	std::mutex delivered_mtx;
	std::this_thread::sleep_for(std::chrono::seconds(30));
	delivered_mtx.lock();
	std::cout << r_food(order_list.back()) <<" delivered\n";
	delivered_mtx.unlock();
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
	std::mutex order_list_access;
	order_list_access.lock();
	for (int i = 0; i < order_list.size(); i++)
	{
		std::cout << r_food(order_list[i]) << std::endl;
	}
	order_list_access.unlock();
}