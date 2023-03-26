/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "USSPTelemetry.h"
#include "Vehicle.h"
#include <USSP/services/dispatcher.h>
#include <USSP/flightBlender/flightID.h>

/// USSP per vehicle management class.

class USSPVehicle : public QObject
{
    Q_OBJECT
public:
    USSPVehicle        (std::shared_ptr<Dispatcher> dispatcher,const Vehicle& vehicle);
    ~USSPVehicle       () override = default;

    // void startTelemetryStream   () override;
    // void stopTelemetryStream    () override;
    // bool isTelemetryStreaming   () override;

// signals:
    // void error                  (const QString& what, const QString& USSPdMessage, const QString& USSPdDetails);

// public slots:
    // void endFlight              () override;

protected slots:
    void vehicleMavlinkMessageReceived(const mavlink_message_t& message) ;

// private slots:
    //void _flightIDChanged       (QString flightID);

private:
    //USSPSharedState&           _shared;
    //USSPFlightManager          _flightManager;
    USSPTelemetry                _telemetry;
    //USSPTrafficMonitor         _trafficMonitor;
    std::shared_ptr<Dispatcher>  _dispatcher;
    flightBlender::FlightID      _flightID;
};
