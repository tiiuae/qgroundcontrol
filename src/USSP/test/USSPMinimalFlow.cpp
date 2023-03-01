/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "USSPMinimalFlow.h"

//-----------------------------------------------------------------------------
USSPMinimalFlow::USSPMinimalFlow(const Vehicle& vehicle):_vehicle(vehicle)
{
   connect(&_vehicle, &Vehicle::mavlinkMessageReceived, this, &USSPMinimalFlow::vehicleMessageReceived);
   dispatcher = new Dispatcher();
}

void USSPMinimalFlow::vehicleMessageReceived(const mavlink_message_t& message)
{
    dispatcher->add_task([message]() {
      switch (message.msgid) {
         case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
            qDebug() << " REST API Call to Submit MAVLINK Message of type MAVLINK_MSG_ID_GLOBAL_POSITION_INT" ;
         break;
         case MAVLINK_MSG_ID_GPS_RAW_INT:
            qDebug() << " REST API Call to Submit MAVLINK Message of type MAVLINK_MSG_ID_GPS_RAW_INT" ;
         break;
         }
        }); 

}
//-----------------------------------------------------------------------------