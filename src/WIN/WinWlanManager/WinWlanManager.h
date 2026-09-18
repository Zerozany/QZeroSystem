_Pragma("once");
#include <QObject>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef QZeroSystem
        #define QZERO_API Q_DECL_EXPORT
    #else
        #define QZERO_API Q_DECL_IMPORT
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define QZERO_API __attribute__((visibility("default")))
#else
    #define QZERO_API
#endif

class QZERO_API WinWlanManager : public QObject
{
    using HANDLE = void*;
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) -> WinWlanManager*;

    ~WinWlanManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(WinWlanManager)

protected:
    explicit(true) WinWlanManager(QObject* _parent = nullptr);

private:
    auto init() noexcept -> void;

public:
    auto getWifiList() noexcept -> QMap<QString, quint8>;

    auto currentWifiName() noexcept -> QString;

    [[nodiscard]] auto disconnectWifi() noexcept -> bool;

    [[nodiscard]] auto connectToWifi(const std::string& _ssid, const std::string& _password) noexcept -> bool;

private:
    HANDLE m_hClient{nullptr};
};
