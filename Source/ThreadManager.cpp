#include "ThreadManager.h"



ThreadManager::ThreadManager()
	: maxThreadsNumber(std::thread::hardware_concurrency())
{
	std::cout << "maxThreadsNumber: " << maxThreadsNumber << std::endl;
}


ThreadManager::~ThreadManager()
{
}

void ThreadManager::addTask(const Task & task)
{
	//threads.emplace_back(task);
}
