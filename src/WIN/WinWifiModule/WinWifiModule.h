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

class QZERO_API WinWifiModule : public QObject
{
    using HANDLE = void*;
    Q_OBJECT
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> WinWifiModule*;

    ~WinWifiModule() noexcept = default;

private:
    explicit(true) WinWifiModule(QObject* _parent = nullptr);

    auto init() noexcept -> void;

public:
    auto getWifiList() noexcept -> std::map<std::string, std::string>;

    auto getCurrentWifi() noexcept -> std::string;

    [[nodiscard]] auto disconnectWifi() noexcept -> bool;

    auto connectWifi(const std::string& _ssid, const std::string& _password) noexcept -> bool;

private:
    HANDLE m_hClient{nullptr};
};
