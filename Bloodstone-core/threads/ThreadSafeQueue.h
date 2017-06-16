#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#pragma once
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

namespace bs {
	namespace threads {

template <typename T>
class ThreadSafeQueue
{
public:
	~ThreadSafeQueue() {
		invalidate();
	}

	bool tryPop(T& out) {
		std::lock_guard<std::mutex> lock{ m_Mutex };
		if (m_Queue.empty() || !m_Valid) {
			return false;
		}
		out = std::move(m_Queue.front());
		m_Queue.pop();
		return true;
	}

	bool waitPop(T& out) {
		std::unique_lock<std::mutex> lock{ m_Mutex };
		m_Condition.wait(lock, [this]() {return !m_Queue.empty() || !m_Valid; });
		if (!m_Valid) {
			return false;
		}
		out = std::move(m_Queue.front());
		m_Queue.pop();
		return true;
	}

	void push(T value) {
		std::lock_guard<std::mutex> lock{ m_Mutex };
		m_Queue.push(std::move(value));
		m_Condition.notify_one();
	}

	bool empty() const {
		std::lock_guard<std::mutex> lock{ m_Mutex };
		return m_Queue.empty();
	}

	void clear() {
		std::lock_guard<std::mutex> lock{ m_Mutex };
		while (!m_Queue.empty()) {
			m_Queue.pop();
		}
		m_Condition.notify_all();
	}

	void invalidate() {
		std::lock_guard<std::mutex> lock{ m_Mutex };
		m_Valid = false;
		m_Condition.notify_all();
	}

	bool isValid() const {
		std::lock_guard<std::mutex> lock{ m_Mutex };
		return m_Valid;
	}

private:
	std::atomic_bool m_Valid{ true };
	mutable std::mutex m_Mutex;
	std::queue<T> m_Queue;
	std::condition_variable m_Condition.

};

	}
}

#endif