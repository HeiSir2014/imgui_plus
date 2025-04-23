#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
//
#include "../base/event.h"
//
#include <imgui.h>

namespace ImGuiPlus {

// base class for all controls
class Control : public EventEmitter {
 public:
  Control(const std::string& name) : name(name) {}

  virtual ~Control() = default;

  virtual void setPosition(float x, float y) {
    position[0] = x;
    position[1] = y;
  }

  virtual void setSize(float width, float height) {
    size[0] = width;
    size[1] = height;
  }

  virtual bool visible() { return is_visible; }

  virtual void setVisible(bool visible) { is_visible = visible; }

  virtual bool render() {
    if (is_visible) {
      return true;
    }
    return false;
  }

 protected:
  std::string name;
  float position[2] = {-1, -1};
  float size[2] = {-1, -1};

  bool is_hover = false;
  bool is_visible = true;
};

class Button : public Control {
 public:
  Button(const std::string& name) : Control(name) {}
  ~Button() override = default;

  bool render() override {
    if (!Control::render()) {
      return false;
    }
    if (position[0] == -1 && position[1] == -1 && size[0] == -1 && size[1] == -1) {
      ImGui::Button(name.c_str());
    } else {
      ImGui::SetCursorPos({position[0], position[1]});
      if (ImGui::Button(name.c_str(), {size[0], size[1]})) {
        this->dispatch({EventType::Click, this});
      }
    }
    return true;
  }
};

class Text : public Control {
 public:
  Text(const std::string& name, const std::string& content)
      : Control(name), content(content) {}
  ~Text() override = default;

  bool render() override {
    if (!Control::render()) {
      return false;
    }
    if (!(position[0] == -1 && position[1] == -1 && size[0] == -1 && size[1] == -1)) {
      ImGui::SetCursorPos({position[0], position[1]});
    }
    ImGui::Text("%s", content.c_str());
    return true;
  }

 private:
  std::string content;
};

class Input : public Control {
 public:
  Input(const std::string& name, std::string defaultValue = "")
      : Control(name), value(defaultValue) {}

  bool render() override {
    ImGui::SetCursorPos({position[0], position[1]});
    value.resize(4096);
    if (ImGui::InputText(name.c_str(), const_cast<char*>(value.c_str()), value.size())) {
      dispatch({EventType::ValueChanged, this});
    }
  }

 private:
  std::string value;
};

}  // namespace ImGuiPlus
