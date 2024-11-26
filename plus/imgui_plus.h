#pragma once
#include <imgui.h>

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace ImGuiPlus {

enum class EventType {
  Click,
  Hover,
  ValueChanged,
};

struct Event {
  EventType type;
  void* sender;  // 触发事件的控件指针
};

using EventCallback = std::function<void(const Event&)>;

class EventManager {
 public:
  void registerEvent(EventType type, EventCallback callback) {
    callbacks[type].emplace_back(std::move(callback));
  }

  void triggerEvent(const Event& event) {
    if (callbacks.find(event.type) != callbacks.end()) {
      for (auto& callback : callbacks[event.type]) {
        callback(event);
      }
    }
  }

 private:
  std::unordered_map<EventType, std::vector<EventCallback>> callbacks;
};

}  // namespace ImGuiPlus