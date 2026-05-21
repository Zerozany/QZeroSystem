#include "AndroidJNIManager.h"
#include <QCoreApplication>

QString AndroidJNIManager::activityUrl() const
{
    return m_activityUrl;
}

void AndroidJNIManager::setActivityUrl(const QString& _activityUrl)
{
    if (m_activityUrl == _activityUrl)
    {
        return;
    }
    m_activityUrl = _activityUrl;
    Q_EMIT this->activityUrlChanged();
}

AndroidJNIManager::AndroidJNIManager(QObject* _parent) : QObject{_parent}
{
    std::invoke(&AndroidJNIManager::connectSignal2Slot, this);
}

auto AndroidJNIManager::connectSignal2Slot() noexcept -> void
{
    connect(this, &AndroidJNIManager::activityUrlChanged, this, &AndroidJNIManager::onActivityUrlChanged);
}

void AndroidJNIManager::onActivityUrlChanged()
{
#if defined(Q_OS_ANDROID)
    m_callObject = QJniObject{m_activityUrl.toUtf8().constData(), "(Landroid/app/Activity;)V", QNativeInterface::QAndroidApplication::context().object<jobject>()};
#endif
}

auto AndroidJNIManager::instance(QObject* _parent) -> AndroidJNIManager*
{
    static AndroidJNIManager* androidJNIManager{new AndroidJNIManager{_parent}};
    return androidJNIManager;
}
