// TII LICENSE Inlusion
#pragma once
#ifndef USSP_FLIGHT_ID_H_
#define USSP_FLIGHT_ID_H_

#include <iostream>
#include <cstdint>
#include <string>
#include <type_traits>
#include <QDebug>
#include <libevents/libs/cpp/parse/nlohmann_json/include/nlohmann/json.hpp>
using json = nlohmann::ordered_json;

namespace flightBlender {
/// TODO : Check If we need to store Json s or packThem when required ( Depends on Modifications that happen )

class FlightID {

 public:

  FlightID();
  
  struct FlightDetails
  {
    std::string   id;
    std::string   operator_id;
    double        operator_location_lng;
    double        operator_location_lat;
    std::string   operation_description;
    std::string   auth_data_format;
    std::string   auth_data_data;
    std::string   serial_number;
    std::string   registration_number;
  };
  
  void initTestID();
  json getJsonForTelem();
  void setupJsonForTelem();
  
  private:
    FlightDetails flightDetails_;
    json flightDetailsJson_;
  
};

}  // namespace flightBlender

#endif  // USSP_FLIGHT_ID_H_