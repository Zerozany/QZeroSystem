#include "PermissionManager.h"
#include <QCoreApplication>

auto PermissionManager::instance(QObject* _parent) -> PermissionManager*
{
    static PermissionManager* permissionManager{new PermissionManager{_parent}};
    return permissionManager;
}

PermissionManager::PermissionManager(QObject* _parent) : QObject{_parent}
{
}

bool PermissionManager::locationPermissionStatus() const
{
    return this->m_locationPermissionStatus;
}

void PermissionManager::setLocationPermissionStatus(bool _locationPermissionStatus)
{
    if (m_locationPermissionStatus == _locationPermissionStatus)
    {
        return;
    }
    m_locationPermissionStatus = _locationPermissionStatus;
    Q_EMIT this->locationPermissionStatusChanged();
}

auto PermissionManager::requestLocationPermission(const QLocationPermission& _locationPermission) noexcept -> void
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS) || defined(Q_OS_MACOS)
    qApp->requestPermission(_locationPermission, [this](const QPermission& _permission) {
        this->setLocationPermissionStatus(_permission.status() == Qt::PermissionStatus::Granted);
    });
#endif
}
