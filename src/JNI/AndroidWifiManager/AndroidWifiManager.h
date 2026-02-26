_Pragma("once");
#include <QObject>

class QJniObject;

class AndroidWifManager : public QObject
{
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> AndroidWifManager*;

    ~AndroidWifManager() noexcept = default;

private:
    explicit(true) AndroidWifManager(QObject* _parent = nullptr);

    Q_DISABLE_COPY_MOVE(AndroidWifManager)

    auto init() noexcept -> void;

public:
    auto getWifiList() noexcept -> QMap<QString, quint8>;

    auto getCurrentWifi() noexcept -> QString;

    auto connectToWifi(const QString& _ssid, const QString& _password) noexcept -> void;

Q_SIGNALS:

private:
    QJniObject* m_wifiObject{nullptr};
};
