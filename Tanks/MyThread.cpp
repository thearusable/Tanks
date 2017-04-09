#include "MyThread.h"



MyThread::MyThread(std::thread& t)
	: thread(std::move(t))
	, task()
{
	if (!thread.joinable()) throw std::logic_error("Not Joinable!");
	std::cout << "Thread created." << std::endl;
}

MyThread::MyThread(Task & task)
	: task(task)
	, thread(task.function)
{
	if (!thread.joinable()) throw std::logic_error("Not Joinable!");
	std::cout << "Thread created." << std::endl;
}


MyThread::~MyThread()
{
	std::cout << "MyThread destructor" << std::endl;
	thread.join();
}

bool MyThread::joinable() {
	return thread.joinable();
}

void MyThread::interrupt() {
	if (thread.joinable()) {
		std::cout << "try join" << std::endl;
		thread.join();
	}
}
