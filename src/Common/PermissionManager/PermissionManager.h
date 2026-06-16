_Pragma("once");
#include <QObject>
#include <QPermission>

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

class PermissionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool locationPermissionStatus READ locationPermissionStatus WRITE setLocationPermissionStatus NOTIFY locationPermissionStatusChanged)
public:
    static auto instance(QObject* _parent = nullptr) -> PermissionManager*;

    ~PermissionManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(PermissionManager)
public:
    bool locationPermissionStatus() const;
    void setLocationPermissionStatus(bool _locationPermissionStatus);

public:
    auto requestLocationPermission(const QLocationPermission& _locationPermission = QLocationPermission{}) noexcept -> void;

protected:
    explicit(true) PermissionManager(QObject* _parent = nullptr);

Q_SIGNALS:
    void locationPermissionStatusChanged();

private:
    bool m_locationPermissionStatus{};
};
