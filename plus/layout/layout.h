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
#include "../controls/control.h"
//
#include <imgui.h>

namespace ImGuiPlus {

class LayoutManager {
 public:
  virtual void layout(std::vector<std::shared_ptr<Control>>& controls) = 0;
};

// 水平布局：控件按横向排列
class HorizontalLayout : public LayoutManager {
 public:
  void layout(std::vector<std::shared_ptr<Control>>& controls) override {
    float xPos = 0.0f;
    for (auto& control : controls) {
      control->setPosition(xPos, 0);
      xPos += control->size[0] + 10;  // 控件之间的间隔
    }
  }
};

// 垂直布局：控件按纵向排列
class VerticalLayout : public LayoutManager {
 public:
  void layout(std::vector<std::shared_ptr<Control>>& controls) override {
    float yPos = 0.0f;
    for (auto& control : controls) {
      control->setPosition(0, yPos);
      yPos += control->size[1] + 10;  // 控件之间的间隔
    }
  }
};

// 网格布局：控件按网格排列
class GridLayout : public LayoutManager {
 public:
  void layout(std::vector<std::shared_ptr<Control>>& controls) override {
    int columns = 3;
    float xPos = 0.0f;
    float yPos = 0.0f;
    for (size_t i = 0; i < controls.size(); ++i) {
      controls[i]->setPosition(xPos, yPos);
      if ((i + 1) % columns == 0) {
        yPos += controls[i]->size[1] + 10;
        xPos = 0;
      } else {
        xPos += controls[i]->size[0] + 10;
      }
    }
  }
};

}  // namespace ImGuiPlus