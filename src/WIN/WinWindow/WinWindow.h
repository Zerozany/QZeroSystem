_Pragma("once");
#include <QQuickWindow>
#include <QtQml/qqmlregistration.h>

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

class QZERO_API WinWindow : public QQuickWindow
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ZeroWindow)
public:
    explicit(true) WinWindow(QQuickWindow* _parent = nullptr);
    ~WinWindow() noexcept = default;

public:
    virtual auto connectSignal2Slot() noexcept -> void = 0;

private:
    auto setWindowPropertys() noexcept -> void;

Q_SIGNALS:

private Q_SLOTS:

private:
};
