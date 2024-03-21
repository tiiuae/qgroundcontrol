/****************************************************************************
 *
 * (c) 2023 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick          2.3

Item {
    // Dummy Properties
    property var    map
    property var    myGeoFenceController
    property var    currentMissionItems
    property bool   interactive:            false
    property bool   planView:               false
    property var    homePosition
    property bool   resetCheck:             false
    property var    _dummy:              myGeoFenceController.polygons

    Instantiator {
        model: _dummy

        delegate : UTMSPMapPolygonVisuals {

        }
    }

}
