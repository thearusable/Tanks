#ifndef _THREAD_MANAGER_H
#define _THREAD_MANAGE_H

#pragma once
#include <vector>
#include <memory>

#include "MyThread.h"

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void addTask(const Task& task);

protected:
	std::vector<std::shared_ptr<MyThread>> threads;
	int maxThreadsNumber;
};

#endif
