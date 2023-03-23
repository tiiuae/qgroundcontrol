/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "USSPTelemetry.h"
#include "QGCMAVLink.h"


//-----------------------------------------------------------------------------
USSPTelemetry::USSPTelemetry(Dispatcher& dispatcher) : _dispatcher(dispatcher), _telemData()
{
    qCInfo(USSPManagerLog) << " USSPTelemetry Constructor" ;
    _timerLastSent.start();
    //counter = 0;
}

void USSPTelemetry::passFlightDetails(json FlightDetailsJson)
{
    _telemData.setFlightDetails(FlightDetailsJson);
}

//-----------------------------------------------------------------------------
void
USSPTelemetry::vehicleMessageReceived(const mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        _handleGlobalPositionInt(message);
        break;
    case MAVLINK_MSG_ID_GPS_RAW_INT:
        _handleGPSRawInt(message);
        break;
    }
}

void
USSPTelemetry::_handleGPSRawInt(const mavlink_message_t& message)
{
    mavlink_gps_raw_int_t gps_raw;
    mavlink_msg_gps_raw_int_decode(&message, &gps_raw);
    if (gps_raw.eph == UINT16_MAX) {
        _lastHdop = 1.f;
    } else {
        _lastHdop = gps_raw.eph / 100.f;
    }
}

//-----------------------------------------------------------------------------
void
USSPTelemetry::_handleGlobalPositionInt(const mavlink_message_t& message)
{   
    // rate-limit updates to 1 Hz
    if (!_timerLastSent.hasExpired(1000)) {
         return;
    }
    _timerLastSent.restart();

    mavlink_global_position_int_t globalPosition;
    mavlink_msg_global_position_int_decode(&message, &globalPosition);

    _telemData.initDefaultRIDdata();
    _telemData.updateRidData(globalPosition,_lastHdop);
    _telemData.setupJson();
    json temp = _telemData.packJson();
    // _response.clear();

    // _dispatcher.add_task([temp,this]() {

    //    std::cout << temp.dump() << std::endl;
    //    std::cout << "____________________________________________________________________" << std::endl;
    //    counter ++;

    //    _response = "Hello";

    // }); 
    std::cout << temp.dump(4) << std::endl;
    std::cout << "_________________________________________________________________________" << std::endl;

    //    json responseJson = json::parse(_response);

    //    if (responseJson.contains("message"){
    //         if(responseJson["message"] == ""){

    //             auto now = std::chrono::system_clock::now();
    //             std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    //             char buffer[20];
    //             std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));

    //             std::cout << counter << " th Telem RID data submitted at " << buffer << std::endl;
    //             std::cout << "____________________________________________________________________" << std::endl;

    //         }
    //    }
       

}

