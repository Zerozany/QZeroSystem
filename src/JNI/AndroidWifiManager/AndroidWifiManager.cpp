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
    QJniObject result{m_wifiObject->callObjectMethod("getWifiList", "()Ljava/lang/String;")};
    if (!result.isValid())
    {
        return wifiMap;
    }
    if (result.toString() == QString{"NULL"})
    {
        return wifiMap;
    }
    QStringList wifiStrList{result.toString().replace("\"", "").split('\n', Qt::SkipEmptyParts)};
    if (wifiStrList.isEmpty())
    {
        return wifiMap;
    }
    for (QString& entry : wifiStrList)
    {
        QStringList parts{entry.replace(entry.lastIndexOf(' '), 1, ",").split(',')};
        wifiMap[parts[0].trimmed()] = parts[1].trimmed().toInt() + 100;
    }
#endif
    return wifiMap;
}

auto AndroidWifManager::getCurrentWifi() noexcept -> QString
{
    QString curConnectedWifiStr{};
#if defined(Q_OS_ANDROID)
    do
    {
        QJniObject result{m_wifiObject->callObjectMethod("getCurrentWifi", "()Ljava/lang/String;")};
        if (!result.isValid())
        {
            break;
        }
        if (result.toString() == QString{"NULL"})
        {
            break;
        }
        curConnectedWifiStr = result.toString();
    } while (false);
#endif
    return curConnectedWifiStr;
}

auto AndroidWifManager::connectToWifi(const QString& _ssid, const QString& _password) noexcept -> void
{
#if defined(Q_OS_ANDROID)
    m_wifiObject->callMethod<void>("connectToWifi", "(Ljava/lang/String;Ljava/lang/String;)V",
                                   QJniObject::fromString(_ssid).object<jstring>(),
                                   QJniObject::fromString(_password).object<jstring>());
#endif
}
