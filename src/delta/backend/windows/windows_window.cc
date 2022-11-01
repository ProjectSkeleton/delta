#include "windows_window.hh"

namespace Delta {

WindowsWindow::WindowsWindow(const WindowInfo& window_info) {
}

bool WindowsWindow::IsOpen() const {
  return true;
}

void WindowsWindow::PollEvents() {
}

void WindowsWindow::OnRenderPassBegin(const RenderPassInfo& render_pass_info) {
}

void WindowsWindow::OnRenderPassComplete(const RenderPassInfo& render_pass_info) {
}

void WindowsWindow::SetResizeCallback(RenderTargetResizeCallback callback) {
}

}
