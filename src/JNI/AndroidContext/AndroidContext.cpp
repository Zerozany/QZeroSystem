#include "AndroidContext.h"
#include <QCoreApplication>

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
#endif

auto AndroidContext::instance(QObject* _parent) noexcept -> AndroidContext*
{
    static AndroidContext* androidContext{new AndroidContext{_parent}};
    return androidContext;
}

AndroidContext::AndroidContext(QObject* _parent) : QObject{_parent}
{
}

auto AndroidContext::context() noexcept -> QJniObject*
{
#if defined(Q_OS_ANDROID)
    static QJniObject jniContext{QNativeInterface::QAndroidApplication::context()};
    if (!jniContext.isValid())
    {
        return nullptr;
    }
    return &jniContext;
#endif
}
