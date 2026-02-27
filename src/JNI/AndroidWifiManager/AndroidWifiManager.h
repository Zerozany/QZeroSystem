_Pragma("once");
#include <QObject>

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
#endif

class AndroidWifiManager : public QObject
{
    Q_OBJECT
public:
    explicit(true) AndroidWifiManager(const QString& _activityPath, QObject* _parent = nullptr);

    ~AndroidWifiManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(AndroidWifiManager)

private:
    auto init() noexcept -> void;

public:
    virtual auto getWifiList(const char* _jniApiName) noexcept -> QMap<QString, quint8>;

    virtual auto currentWifiName(const char* _jniApiName) noexcept -> QString;

    virtual auto connectToWifi(const char* _jniApiName, const QString& _ssid, const QString& _password) noexcept -> void;

Q_SIGNALS:

private:
#if defined(Q_OS_ANDROID)
    QJniObject m_wifiObject{};
#endif
    QString m_activityPath{};
};
