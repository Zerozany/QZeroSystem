#include "AndroidWifiManager.h"
#include <QDebug>
#include <QCoreApplication>
#include <QStringList>

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
    #include "AndroidContext.h"
#endif

#if defined(Q_OS_ANDROID)

// extern "C" JNIEXPORT void JNICALL
// Java_com_sonixbeauty_module_WifiModule_connectSuccess(JNIEnv* env, jobject thiz, jint state)
// {
//     Q_UNUSED(env);
//     Q_UNUSED(thiz);
//     AndroidWifManager* androidWifiConfig{AndroidWifManager::instance()};
//     if (androidWifiConfig)
//     {
//         Q_EMIT androidWifiConfig->wifiStateChanged(static_cast<AndroidWifManager::WifiState>(state));
//     }
// }
#endif

auto AndroidWifManager::instance(QObject* _parent) noexcept -> AndroidWifManager*
{
    static AndroidWifManager* androidWifiConfig{new AndroidWifManager{_parent}};
    return androidWifiConfig;
}

AndroidWifManager::AndroidWifManager(QObject* _parent) : QObject{_parent}
{
    std::invoke(&AndroidWifManager::init, this);
}

auto AndroidWifManager::init() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    QJniObject* context{AndroidContext::instance()->context()};
    if (!context || !context->isValid())
    {
        qDebug() << "Failed to get valid context";
        return;
    }
    m_wifiObject = new QJniObject{"com/zerosystem/module/WifiModule", "(Landroid/app/Activity;)V", context->object<jobject>(), this};
    if (!m_wifiObject->isValid())
    {
        qDebug() << "Cannot create Java helper instance";
        return;
    }
#endif
}

auto AndroidWifManager::getWifiList() noexcept -> QMap<QString, quint8>
{
    QMap<QString, quint8> wifiMap{};
#if defined(Q_OS_ANDROID)
    // 调用 Java 方法，获取 HashMap
    QJniObject result{m_wifiObject->callObjectMethod("getWifiMap", "()Ljava/util/HashMap;")};
    if (!result.isValid())
    {
        return wifiMap;
    }
    QJniObject entrySet{result.callObjectMethod("entrySet", "()Ljava/util/Set;")};
    QJniObject iterator{entrySet.callObjectMethod("iterator", "()Ljava/util/Iterator;")};
    while (iterator.callMethod<jboolean>("hasNext"))
    {
        QJniObject entry{iterator.callObjectMethod("next", "()Ljava/lang/Object;")};
        QJniObject key{entry.callObjectMethod("getKey", "()Ljava/lang/Object;")};
        QJniObject value{entry.callObjectMethod("getValue", "()Ljava/lang/Object;")};
        QString    ssid{key.toString()};
        int        level{value.callMethod<jint>("intValue")};
        wifiMap.insert(ssid, level);
    }
#endif
    return wifiMap;
}

auto AndroidWifManager::getCurrentWifi() noexcept -> QString
{
#if defined(Q_OS_ANDROID)
    QJniObject result{m_wifiObject->callObjectMethod("getCurrentWifi", "()Ljava/lang/String;")};
    if (!result.isValid())
    {
        return QString{};
    }
    return result.toString();
#else
    return QString{};
#endif
}

auto AndroidWifManager::connectToWifi(const QString& _ssid, const QString& _password) noexcept -> void
{
#if defined(Q_OS_ANDROID)
    m_wifiObject->callMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V",
                                   QJniObject::fromString(_ssid).object<jstring>(),
                                   QJniObject::fromString(_password).object<jstring>());
#endif
}
