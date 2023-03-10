/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "QGCLoggingCategory.h"
#include "QGCToolbox.h"

#include <USSP/services/dispatcher.h>

#include <memory>
#include <QTimer>
#include <QDebug>

class QGCToolbox;
class USSPVehicle;
class Vehicle;
//class Dispatcher;


Q_DECLARE_LOGGING_CATEGORY(USSPManagerLog)

//-----------------------------------------------------------------------------
/**
 * @class USSPManager
 * FlightBlender implementation of USSP
 */

class USSPManager : public QGCTool
{
    Q_OBJECT
public:
    USSPManager(QGCApplication* app, QGCToolbox* toolbox);
    virtual ~USSPManager();

    void setToolbox (QGCToolbox* toolbox);

    QString                         providerName                            () const { return QString("FlightBlender"); }
    USSPVehicle*                    instantiateVehicle                      (const Vehicle& vehicle);

private:
    USSPVehicle*                    vehicle_                                 = nullptr;
    //TODO: REST API Dependent 
    //bool                            connected                               () const override;
    //QString                         connectStatus                           () const override { return _connectStatus; }
    //AirspaceManager::AuthStatus     authStatus                              () const override { return _authStatus; }
    Dispatcher _dispatcher; 
};
