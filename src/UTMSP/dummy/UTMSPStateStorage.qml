/****************************************************************************
 *
 * (c) 2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

pragma Singleton
import QtQuick

QtObject {
    property bool loginState: true
    property bool registerButtonState: true
    property bool removeFlightPlanState: false
    property bool showActivationTab: false
    property string startTimeStamp: ""
    property string flightID: ""
}
