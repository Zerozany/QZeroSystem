#include "AndroidJNIManager.h"
#include "AndroidContext.h"
#include <QCoreApplication>

QString AndroidJNIManager::activityName() const
{
    return m_activityName;
}

void AndroidJNIManager::setActivityName(const QString& _activityName)
{
    if (m_activityName == _activityName)
    {
        return;
    }
    m_activityName = _activityName;
    Q_EMIT this->activityNameChanged();
}

AndroidJNIManager::AndroidJNIManager(QObject* _parent) : QObject{_parent}
{
    std::invoke(&AndroidJNIManager::connectSignal2Slot, this);
}

auto AndroidJNIManager::connectSignal2Slot() noexcept -> void
{
    connect(this, &AndroidJNIManager::activityNameChanged, this, &AndroidJNIManager::onActivityNameChanged);
}

void AndroidJNIManager::onActivityNameChanged()
{
#if defined(Q_OS_ANDROID)
    m_callObject = QJniObject{m_activityName.toUtf8().constData(), "(Landroid/app/Activity;)V", QNativeInterface::QAndroidApplication::context().object<jobject>()};
#endif
}

auto AndroidJNIManager::instance(QObject* _parent) -> AndroidJNIManager*
{
    static AndroidJNIManager* androidJNIManager{new AndroidJNIManager{_parent}};
    return androidJNIManager;
}
