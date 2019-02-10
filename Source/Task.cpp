#include "Task.h"



Task::Task(void)
	: function(nullptr)
{
}

Task::Task(const Task& t)
	: function(t.function)
{}


Task::~Task()
{
}

void Task::operator=(std::function<void()> fun)
{
	this->function = fun;
}
