#ifndef _MYTHREAD_H
#define _MYTHREAD_H

#pragma once
#include <thread>
#include <iostream>
#include "Task.h"

class interrupt_exception : public std::exception {
public:
	virtual char const* what() const override {
		return "thread interrupted";
	}
};


class MyThread
{
private:
	std::thread thread;
	Task task;

public:
	explicit MyThread(std::thread& t);
	explicit MyThread(Task& task);
	~MyThread();

	bool joinable();
	void interrupt();

	MyThread(MyThread& obj) = delete;
	MyThread& operator=(const MyThread& obj) = delete;
};

#endif