_Pragma("once");
#include <QObject>

class QJniObject;

class AndroidContext : public QObject
{
public:
    static auto instance(QObject* _parent = nullptr) noexcept -> AndroidContext*;

    ~AndroidContext() noexcept = default;

public:
    auto context() noexcept -> QJniObject*;

private:
    explicit(true) AndroidContext(QObject* _parent = nullptr);

    Q_DISABLE_COPY_MOVE(AndroidContext)
};
