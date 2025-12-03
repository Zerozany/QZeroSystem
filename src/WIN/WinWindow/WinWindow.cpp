#include "WinWindow.h"

WinWindow::WinWindow(QQuickWindow* _parent) : QQuickWindow{_parent}
{
    std::invoke(&WinWindow::setWindowPropertys, this);
    std::invoke(&WinWindow::connectSignal2Slot, this);
}

auto WinWindow::connectSignal2Slot() noexcept -> void
{
}

auto WinWindow::setWindowPropertys() noexcept -> void
{
#if defined(Q_OS_WINDOWS)
    this->setVisibility(QWindow::Maximized);
#endif
}
