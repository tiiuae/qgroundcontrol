/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QGCMAVLink.h>
#include "Vehicle.h"

#include <QObject>
#include <QElapsedTimer>
#include <QDebug>
#include <USSP/services/dispatcher.h>
#include <USSP/flightBlender/telemetry.h>

// TODO: Start & Stop Streaming
// TODO: and Time start based on the same
/// Class to send telemetry data to AirMap
class USSPTelemetry : public QObject
{
    Q_OBJECT
public:
    USSPTelemetry                 (Dispatcher& dispatcher);
    ~USSPTelemetry        () = default;

    void passFlightDetails(json FlightDetailsJson);

//signals:
    //void error                      (const QString& what, const QString& airmapdMessage, const QString& airmapdDetails);

public slots:
    void vehicleMessageReceived     (const mavlink_message_t& message);

private:

    void _handleGlobalPositionInt   (const mavlink_message_t& message);
    void _handleGPSRawInt           (const mavlink_message_t& message);

    enum class State {
        Idle,
        StartCommunication,
        EndCommunication,
        Streaming,
    };

    State                        _state = State::Idle;
    QString                      _flightID;
    float                        _lastHdop = 1.f;
    QElapsedTimer                _timerLastSent;
    Dispatcher&                  _dispatcher;
    flightBlender::Telemetry     _telemData;
    //int                          counter;
    //std::string                  _response;
};
