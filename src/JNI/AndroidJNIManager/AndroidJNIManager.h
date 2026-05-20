_Pragma("once");
#include <QObject>

#if defined(Q_OS_ANDROID)
    #include <QJniObject>
    #include <QJniEnvironment>
#endif

class AndroidJNIManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString activityName READ activityName WRITE setActivityName NOTIFY activityNameChanged)
public:
    static auto instance(QObject* _parent = nullptr) -> AndroidJNIManager*;

    ~AndroidJNIManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(AndroidJNIManager)

public:
    QString activityName() const;
    void    setActivityName(const QString& _activityName);

public:
    template <typename ReturnType = void, typename... Args>
    auto callJNIMethod(const QString& _jniMethod, const QString& _jniType, Args... _args) noexcept -> ReturnType;

private:
    explicit(true) AndroidJNIManager(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void activityNameChanged();

private Q_SLOTS:
    void onActivityNameChanged();

private:
#if defined(Q_OS_ANDROID)
    QJniObject m_callObject{};
#endif
    QString m_activityName{};
};

template <typename ReturnType, typename... Args>
inline auto AndroidJNIManager::callJNIMethod(const QString& _jniMethod, const QString& _jniType, Args... _args) noexcept -> ReturnType
{
#if defined(Q_OS_ANDROID)

    if constexpr (std::is_void_v<ReturnType>)
    {
        m_callObject.callMethod<ReturnType>(_jniMethod.toUtf8().constData(), _jniType.toUtf8().constData(), _args...);
    }
    else
    {
        ReturnType value{m_callObject.callMethod<ReturnType>(_jniMethod.toUtf8().constData(), _jniType.toUtf8().constData(), _args...)};
        return value;
    }

#endif
    if constexpr (!std::is_void_v<ReturnType>)
    {
        return ReturnType{};
    }
}
