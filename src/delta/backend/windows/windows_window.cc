#include "windows_window.hh"

namespace Delta {

WindowsWindow::WindowsWindow(const WindowCreateInfo& window_info) {
}

bool WindowsWindow::IsOpen() const {
  return true;
}

void WindowsWindow::PollEvents() {
}

void WindowsWindow::OnRenderPassBegin() {
}

void WindowsWindow::OnRenderPassComplete() {
}

void WindowsWindow::SetResizeCallback(WindowResizeCallback callback) {
}

}
