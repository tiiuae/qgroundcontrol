#pragma once

#include <iostream>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>

class Dispatcher 
{
public:
  Dispatcher() : running_(true) 
  {
    workerThread_ = std::thread([this]() {
      while (running_) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(queueMutex_);
          conditionVariable_.wait(lock, [this] { return !tasks_.empty() || !running_; });
          if (!running_ && tasks_.empty()) {
            return;
          }
          task = std::move(tasks_.front());
          tasks_.pop_front();
        }
        task();
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    });
    // workerThread_.join();
  }

  ~Dispatcher() 
  {
    std::cout<<" DESTRUCTOR is the problem "<<std::endl;
    {
      std::unique_lock<std::mutex> lock(queueMutex_);
      running_ = false;
    }
    conditionVariable_.notify_all();
    workerThread_.join();
  }

  void add_task(std::function<void()> task) 
  {
    {
      std::unique_lock<std::mutex> lock(queueMutex_);
      tasks_.push_back(std::move(task));
    }
    conditionVariable_.notify_one();
  }

private:
  std::deque<std::function<void()>> tasks_;
  std::mutex queueMutex_;
  std::condition_variable conditionVariable_;
  std::thread workerThread_;
  bool running_;
};