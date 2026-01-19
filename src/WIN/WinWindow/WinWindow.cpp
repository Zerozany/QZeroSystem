#include "WinWindow.h"

static constexpr float ratio{0.7};

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
    QRect availableGeometry{this->screen()->availableGeometry()};
    this->setGeometry(availableGeometry.x() + (availableGeometry.width() - availableGeometry.width() * ratio) / 2,
                      availableGeometry.y() + (availableGeometry.height() - availableGeometry.height() * ratio) / 2,
                      availableGeometry.width() * ratio,
                      availableGeometry.height() * ratio);
    this->setVisibility(QWindow::Windowed);
}
