#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace ImGuiPlus {

class Control;

enum class EventType {
  Click,
  Hover,
  ValueChanged,
};

struct Event {
  EventType type;
  Control* sender;  // 触发事件的控件指针
};

using EventCallback = std::function<void(const Event&)>;

class EventEmitter {
 public:
  EventEmitter() = default;
  virtual ~EventEmitter() = default;

  virtual void addEventListener(EventType type, const EventCallback& callback) {
    callbacks[type].emplace_back(callback);
  }

  virtual void removeEventListener(EventType type, const EventCallback& callback) {
    if (callbacks.find(type) != callbacks.end()) {
      auto& eventCallbacks = callbacks[type];
      eventCallbacks.erase(std::remove_if(eventCallbacks.begin(), eventCallbacks.end(), [&](const EventCallback& cb) {
                             return cb.target<EventCallback>() == callback.target<EventCallback>();
                           }),
                           eventCallbacks.end());
    }
  }

  virtual void dispatch(const Event& event) {
    if (callbacks.find(event.type) == callbacks.end()) {
      return;
    }
    for (auto& callback : callbacks[event.type]) {
      if (callback) callback(event);
    }
  }

 private:
  std::unordered_map<EventType, std::vector<EventCallback>> callbacks;
};

}  // namespace ImGuiPlus