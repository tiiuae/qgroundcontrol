/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "USSPVehicle.h"

///TODO : Find a way to initialize Flight ID
//-----------------------------------------------------------------------------
USSPVehicle::USSPVehicle(Dispatcher& dispatcher,const Vehicle& vehicle) : 
    _telemetry(dispatcher),
    _dispatcher(dispatcher),
    _flightID()
{
    qCInfo(USSPManagerLog) << " USSPVehicle Contructor" ;
    connect(&vehicle, &Vehicle::mavlinkMessageReceived, this, &USSPVehicle::vehicleMavlinkMessageReceived);
    qCInfo(USSPManagerLog) << " USSPVehicle MAvlink msg slot connected" ;
    // TODO: Connect REverse Slots to see if it is possible

    _telemetry.passFlightDetails(_flightID.getJsonForTelem());
    
}


//-----------------------------------------------------------------------------
void
USSPVehicle::vehicleMavlinkMessageReceived(const mavlink_message_t& message)
{       
    _telemetry.vehicleMessageReceived(message);
}

