#ifndef _TASK_H
#define _TASK_H

#pragma once
#include <functional>


class Task
{
public:
	Task(void);
	Task(const Task& t);

	~Task();

	void operator=(std::function<void()> fun);
	void operator=(Task& t) = delete;

	std::function<void()> function;
};

#endif