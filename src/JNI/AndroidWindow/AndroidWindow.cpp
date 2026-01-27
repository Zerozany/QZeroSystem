#include "AndroidWindow.h"

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
#endif

AndroidWindow::AndroidWindow(QQuickWindow* _parent) : QQuickWindow{_parent}
{
    std::invoke(&AndroidWindow::setAndroidWindow, this);
    std::invoke(&AndroidWindow::connectSignal2Slot, this);
    std::invoke(&AndroidWindow::setWindowPropertys, this);
}

AndroidWindow::~AndroidWindow() noexcept
{
    if (m_instance == this)
    {
        m_instance = nullptr;
    }
}

auto AndroidWindow::instance() noexcept -> AndroidWindow*
{
    return m_instance;
}

auto AndroidWindow::setAndroidWindow() noexcept -> void
{
    if (m_instance == this)
    {
        return;
    }
    m_instance = this;
}

void AndroidWindow::onActivityVisibileChanged(bool _activityVisibile)
{
    if (_activityVisibile)
    {
        this->setVisible(true);
    }
    else
    {
        this->setVisible(false);
    }
}

auto AndroidWindow::setWindowPropertys() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    this->setGraphicsApi(QSGRendererInterface::OpenGL);
    this->setFlags(Qt::Window | Qt::ExpandedClientAreaHint);
    this->setVisibility(QWindow::FullScreen);
#endif
}

auto AndroidWindow::connectSignal2Slot() noexcept -> void
{
#if defined(Q_OS_ANDROID)

    connect(this, &AndroidWindow::activityVisibileChanged, this, &AndroidWindow::onActivityVisibileChanged, Qt::QueuedConnection);

#endif
}
