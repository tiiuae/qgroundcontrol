/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once
//#include "LifetimeChecker.h"


#include <USSP/services/dispatcher.h>

#include "Vehicle.h"

#include <memory>
#include <QGCMAVLink.h>
#include <QObject>
#include <QTimer>
#include <QDebug>

class USSPMinimalFlow : public QObject
{
    Q_OBJECT
public:

    USSPMinimalFlow(const Vehicle& vehicle);

public slots:

    void vehicleMessageReceived(const mavlink_message_t& message);

protected:

    const Vehicle& _vehicle;

private:
   Dispatcher* dispatcher = nullptr;
};