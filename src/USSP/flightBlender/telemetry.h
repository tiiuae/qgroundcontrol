// TII LICENSE Inlusion
#pragma once
#ifndef USSP_TELEMETRY_H_
#define USSP_TELEMETRY_H_

// TODO: Check the requirement of Headers with similar functionality
// #include <ussp/do_not_copy_or_move.h>
// #include <ussp/error.h>
// #include <ussp/visibility.h>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <string>
#include <type_traits>
#include <QDebug>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <libevents/libs/cpp/parse/nlohmann_json/include/nlohmann/json.hpp>

#include "QGCMAVLink.h"
using json = nlohmann::ordered_json;

namespace flightBlender {


/// Telemetry provides functionality to submit telemetry updates to the
/// flightBlender services during flight.

// TODO: 1) Check for requirement of Exporting the class 2) Use of DoNotCopyOrMove class (referance to Airmap)
// TODO: flight information data passage, better way ?
// TODO: Implement static assertion needed for json data members
// TODO: Check JSON for required members and set default values after ( Current Version Demo in mind )
// TODO: Check if construtor is required for these headers (My Opinion: NO) - Discuss
// TODO: Check for efficient ways to pack Json
class Telemetry {
 public:

  struct Position {
    double lat;                   ///< The latitude of the position [°].
    double lng;                   ///< The longitude of the position in [°].
    double alt;                   ///< The altitude above mean sea level of the position in [m].
    std::string accuracy_h;            ///< The horizontal accuracy of the position in [m].
    std::string accuracy_v; 
    bool extrpolated;
    double pressure_altitude;
  };

  struct Height{
    double distance;
    std::string reference;
  };

  struct RidData {
    std::string timestamp;    
    double timestamp_accuracy;          
    std::string operational_status;
    Position position;
    double track;
    double speed;
    std::string speed_accuracy;
    double vertical_speed;          
    Height height;
    double group_radius; 
    double group_ceiling;
    double group_floor;
    int group_count;
    std::string group_time_start;
    std::string group_time_end;
  };

  void setFlightDetails(json flightDetailsJson_);
  void initDefaultRIDdata();
  void updateRidData(mavlink_global_position_int_t globalPosition,float lastHdop);
  void setupJson();
  json packJson();
 
  private:
    RidData ridData_;
    json ridDataJson_;
    json flightDetailsJson_;

};

}  // namespace flightBlender

#endif  // USSP_TELEMETRY_H_
