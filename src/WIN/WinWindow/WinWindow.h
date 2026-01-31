_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef QZeroSystem
        #define QZERO_API Q_DECL_EXPORT
    #else
        #define QZERO_API Q_DECL_IMPORT
    #endif
#else
    #define QZERO_API
#endif

class QZERO_API WinWindow : public QQuickWindow
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ZeroWindow)
public:
    explicit(true) WinWindow(QQuickWindow* _parent = nullptr);
    ~WinWindow() noexcept = default;

    static auto instance() noexcept -> WinWindow*;

private:
    auto connectSignal2Slot() noexcept -> void;

    auto setWindowPropertys() noexcept -> void;

Q_SIGNALS:

private Q_SLOTS:

private:
};
