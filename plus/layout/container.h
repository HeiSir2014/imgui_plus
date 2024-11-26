class Container : public Control {
 public:
  Container(const std::string& name, std::shared_ptr<LayoutManager> layout)
      : Control(name), layoutManager(std::move(layout)) {}

  void addControl(std::shared_ptr<Control> control) {
    controls.push_back(std::move(control));
  }

  void render() override {
    layoutManager->layout(controls);  // 布局管理
    for (auto& control : controls) {
      control->render();  // 渲染每个控件
    }
  }

 private:
  std::shared_ptr<LayoutManager> layoutManager;
  std::vector<std::shared_ptr<Control>> controls;
};

}  // namespace ImGuiPlus