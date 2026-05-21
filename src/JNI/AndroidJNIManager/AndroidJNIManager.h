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

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
#endif

class QZERO_API AndroidJNIManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString activityUrl READ activityUrl WRITE setActivityUrl NOTIFY activityUrlChanged)
public:
    static auto instance(QObject* _parent = nullptr) -> AndroidJNIManager*;

    ~AndroidJNIManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(AndroidJNIManager)

public:
    QString activityUrl() const;
    void    setActivityUrl(const QString& _activityUrl);

public:
    template <typename ReturnType = void, typename... Args>
    auto callJNIMethod(const char* _jniMethod, const char* _jniType, Args... _args) noexcept -> ReturnType;

private:
    explicit(true) AndroidJNIManager(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void activityUrlChanged();

private Q_SLOTS:
    void onActivityUrlChanged();

private:
#if defined(Q_OS_ANDROID)
    QJniObject m_callObject{};
#endif
    QString m_activityUrl{};
};

template <typename ReturnType, typename... Args>
inline auto AndroidJNIManager::callJNIMethod(const char* _jniMethod, const char* _jniType, Args... _args) noexcept -> ReturnType
{
#if defined(Q_OS_ANDROID)

    if constexpr (std::is_void_v<ReturnType>)
    {
        m_callObject.callMethod<ReturnType>(_jniMethod, _jniType, _args...);
    }
    else
    {
        return ReturnType{m_callObject.callMethod<ReturnType>(_jniMethod, _jniType, _args...)};
    }

#endif
    if constexpr (!std::is_void_v<ReturnType>)
    {
        return ReturnType{};
    }
}
