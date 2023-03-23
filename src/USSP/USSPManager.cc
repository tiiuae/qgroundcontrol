/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/
#include "USSPVehicle.h"
#include "USSPManager.h"
#include "Vehicle.h"

QGC_LOGGING_CATEGORY(USSPManagerLog, "USSPManagerLog")

//-----------------------------------------------------------------------------
USSPManager::USSPManager(QGCApplication* app, QGCToolbox* toolbox) : QGCTool(app, toolbox), _dispatcher()
{
    qCInfo(USSPManagerLog) << " USSPManager Constructor" ;
}

//-----------------------------------------------------------------------------
USSPManager::~USSPManager()
{
    qCInfo(USSPManagerLog) << " USSPManager Destructor" ;
}

//-----------------------------------------------------------------------------
void
USSPManager::setToolbox(QGCToolbox* toolbox)
{   
    qCInfo(USSPManagerLog) << " USSPManager ToolBox Set" ;
    QGCTool::setToolbox(toolbox);
}

USSPVehicle*                    
USSPManager::instantiateVehicle(const Vehicle& vehicle)
{   
    // TODO: Investigate safe deletion of pointer in this modification of having a member pointer
    vehicle_ = new USSPVehicle(_dispatcher,vehicle);
    //connect(manager, &AirMapVehicleManager::error, this, &AirMapManager::_error);
    return vehicle_;
}