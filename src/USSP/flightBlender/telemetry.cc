// TII LICENSE Inlusion
#include "USSP/flightBlender/telemetry.h"
using json = nlohmann::ordered_json;

void flightBlender::Telemetry::setFlightDetails(json flightDetailsJson_)
{
  this->flightDetailsJson_ = flightDetailsJson_;
}

void flightBlender::Telemetry::initDefaultRIDdata()
{
  ridData_ = {};
  ridData_.timestamp_accuracy = 0.0;
  ridData_.speed_accuracy = "SAUnknown";
  ridData_.height.reference = "GroundLevel";
}  

  
void flightBlender::Telemetry::updateRidData(mavlink_global_position_int_t globalPosition,float accuracy)
{ 


  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::ostringstream oss;
  oss << std::put_time(std::gmtime(&now_c), "%FT%T") << "Z\n";
  
  ridData_.timestamp           = oss.str();
  ridData_.position.lat        = static_cast<double>(globalPosition.lat / 1e7);
  ridData_.position.lng        = static_cast<double>(globalPosition.lon / 1e7);
  ridData_.position.alt        = static_cast<double>(globalPosition.alt) / 1000;
  ridData_.position.accuracy_h = static_cast<double>(accuracy);

  ridData_.track               = static_cast<double>(globalPosition.hdg);

  double vx                    = (globalPosition.vx / 100.f);
  double vy                    = (globalPosition.vy / 100.f);
  ridData_.speed               = std::sqrt(vx*vx + vy*vy);

  ridData_.vertical_speed      = globalPosition.vz / 100.f;

  ridData_.height.distance     = static_cast<double>(globalPosition.relative_alt) / 1000.0;
}

void flightBlender::Telemetry::setupJson()
{     
      ridDataJson_.clear();

      ridDataJson_["timestamp"] = ridData_.timestamp;
      ridDataJson_["timestamp_accuracy"] = ridData_.timestamp_accuracy;
      //ridDataJson_["operational_status"] = ridData_.operational_status;
      ridDataJson_["position"]["lat"] = ridData_.position.lat;
      ridDataJson_["position"]["lng"] = ridData_.position.lng;
      ridDataJson_["position"]["alt"] = ridData_.position.alt;
      ridDataJson_["position"]["accuracy_h"] = ridData_.position.accuracy_h;
      //ridDataJson_["position"]["accuracy_v"] = ridData_.position.accuracy_v;
      //ridDataJson_["position"]["extrpolated"] = ridData_.position.extrpolated;
      //ridDataJson_["position"]["pressure_altitude"] = ridData_.position.pressure_altitude;
      ridDataJson_["track"] = ridData_.track;
      ridDataJson_["speed"] = ridData_.speed;
      ridDataJson_["speed_accuracy"] = ridData_.speed_accuracy;
      ridDataJson_["vertical_speed"] = ridData_.vertical_speed;
      ridDataJson_["height"]["distance"] = ridData_.height.distance;
      ridDataJson_["height"]["reference"] = ridData_.height.reference;
      //ridDataJson_["group_radius"] = ridData_.group_radius;
      //ridDataJson_["group_ceiling"] = ridData_.group_ceiling;
      //ridDataJson_["group_floor"] = ridData_.group_floor;
      //ridDataJson_["group_count"] = ridData_.timestamp;
      //ridDataJson_["group_time_start"] = ridData_.group_time_start;
      //ridDataJson_["group_time_end"] = ridData_.group_time_end;
      //std::cout << ridDataJson_.dump(4) << std::endl;
}

json flightBlender::Telemetry::packJson()
{
    json current_states = json::array();
    current_states.push_back(ridDataJson_);

    json mix;
    mix["current_states"] = current_states;
    mix["flight_details"] = flightDetailsJson_;

    json final_array = json::array();
    final_array.push_back(mix);

    json final_format;
    final_format["observations"] = final_array;

    return final_format;
}