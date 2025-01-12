#include "remotepositionsource.h"
#include "servicefrontend.h"

void RemotePositionSource::setActive(bool active)
{
  if (m_service)
  {
    if (!m_active && active)
    {
      connect(m_service.data(), &ServiceFrontend::positionPositionUpdated, this, &RemotePositionSource::_positionUpdated);
      m_active = true;
      emit activeChanged();
    }
    else if (m_active && !active)
    {
      disconnect(m_service.data(), &ServiceFrontend::positionPositionUpdated, this, &RemotePositionSource::_positionUpdated);
      m_active = false;
      emit activeChanged();
    }
  }
}

void RemotePositionSource::connectToService(QVariant service)
{
  ServiceFrontendPtr _service = service.value<ServiceFrontendPtr>();
  connectToService(_service);
}

void RemotePositionSource::connectToService(ServiceFrontendPtr& service)
{
  if (m_service)
  {
    setActive(false);
  }
  m_service = service;
  if (m_service)
  {
    setActive(true);
  }
}

void RemotePositionSource::_positionUpdated(bool valid, double lat, double lon, bool haccvalid, float hacc, double alt)
{
  m_position.set(valid, lat, lon, haccvalid, hacc, alt);
  emit positionChanged();
}
