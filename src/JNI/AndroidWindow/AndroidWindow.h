_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

class AndroidWindow : public QQuickWindow
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ZeroWindow)
public:
    explicit(true) AndroidWindow(QQuickWindow* _parent = nullptr);
    ~AndroidWindow() noexcept;

    static auto instance() noexcept -> AndroidWindow*;

private:
    auto connectSignal2Slot() noexcept -> void;

    auto setAndroidWindow() noexcept -> void;

    auto setWindowPropertys() noexcept -> void;

Q_SIGNALS:
    void activityVisibileChanged(bool _activityVisibile);

private Q_SLOTS:
    void onActivityVisibileChanged(bool _activityVisibile);

private:
    inline static AndroidWindow* m_instance{nullptr};
};
