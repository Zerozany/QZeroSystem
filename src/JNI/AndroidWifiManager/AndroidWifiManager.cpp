#include "AndroidWifiManager.h"
#include <QDebug>

#if defined(Q_OS_ANDROID)
    #include <QJniEnvironment>
    #include <QJsonDocument>
    #include <QJsonArray>
    #include <QJsonObject>
    #include <QJsonValue>
    #include "AndroidContext.h"
#endif

AndroidWifiManager::AndroidWifiManager(const QString& _activityPath, QObject* _parent) : QObject{_parent}, m_activityPath{_activityPath}
{
    std::invoke(&AndroidWifiManager::init, this);
}

auto AndroidWifiManager::init() noexcept -> void
{
#if defined(Q_OS_ANDROID)
    m_wifiObject = QJniObject{m_activityPath.toUtf8().constData(), "(Landroid/app/Activity;)V", AndroidContext::instance()->context()->object<jobject>()};
    if (!m_wifiObject.isValid())
    {
        qDebug() << "Cannot create Java AndroidWifiManager instance";
        return;
    }
#endif
}

auto AndroidWifiManager::getWifiList(const char* _jniApiName) noexcept -> QMap<QString, quint8>
{
    QMap<QString, quint8> wifiViewMap{};
#if defined(Q_OS_ANDROID)
    QJniObject result{m_wifiObject.callObjectMethod(_jniApiName, "()Ljava/lang/String;")};
    do
    {
        if (!result.isValid())
        {
            qDebug() << "Cannot use Java getWifiList function";
            break;
        }
        QJsonDocument doc{QJsonDocument::fromJson(result.toString().toUtf8())};
        if (!doc.isArray())
        {
            break;
        }
        for (const QJsonValue& value : doc.array())
        {
            wifiViewMap[value.toObject()["ssid"].toString()] = static_cast<quint8>(value.toObject()["level"].toInt());
        }
    } while (false);
#endif
    return wifiViewMap;
}

auto AndroidWifiManager::currentWifiName(const char* _jniApiName) noexcept -> QString
{
    QString currentWifiNameStr{};
#if defined(Q_OS_ANDROID)
    QJniObject result{m_wifiObject.callObjectMethod(_jniApiName, "()Ljava/lang/String;")};
    do
    {
        if (!result.isValid())
        {
            qDebug() << "Cannot use Java currentWifiName function";
            break;
        }
        currentWifiNameStr = result.toString();
    } while (false);
#endif
    return currentWifiNameStr;
}

auto AndroidWifiManager::connectToWifi(const char* _jniApiName, const QString& _ssid, const QString& _password) noexcept -> void
{
#if defined(Q_OS_ANDROID)
    m_wifiObject.callMethod<void>(_jniApiName, "(Ljava/lang/String;Ljava/lang/String;)V",
                                  QJniObject::fromString(_ssid).object<jstring>(),
                                  QJniObject::fromString(_password).object<jstring>());
#endif
}
