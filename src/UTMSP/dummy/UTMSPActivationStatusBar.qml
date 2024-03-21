/****************************************************************************
 *
 * (c) 2023 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick 2.3
import QGroundControl.UTMSP                 1.0

Item {
    property string activationStartTimestamp
    property bool   activationApproval
    property string flightID
    property string timeDifference

    signal  activationTriggered(bool value)
}
