// TII LICENSE Inlusion


#include "USSP/flightBlender/flightID.h"
using json = nlohmann::ordered_json;



flightBlender::FlightID::FlightID()
{
  this->initTestID();
  this->setupJsonForTelem();
}

void flightBlender::FlightID::initTestID()
{
  this->flightDetails_.id                    = "1";
  this->flightDetails_.operator_id           = "f9edf164-1c8f-45d7-9854-bc0ffa33573d";
  this->flightDetails_.operator_location_lng = 46.97615311620088;
  this->flightDetails_.operator_location_lat = 7.476099729537965;
  this->flightDetails_.operation_description = "Delivery operation, see more details at https://deliveryops.com/operation";
  //this->flightDetails_.auth_data_format      = "string";
  //this->flightDetails_.auth_data_data        = "string";
  this->flightDetails_.serial_number         = "INTCJ123-4567-890";
  this->flightDetails_.registration_number   = "FA12345897";

  this->flightDetails_.aircraft_type         = "Helicopter";
  this->flightDetails_.operator_name         = "tii-ssrc";
}

json flightBlender::FlightID::getJsonForTelem() 
{
  return this->flightDetailsJson_;
}

void flightBlender::FlightID::setupJsonForTelem()
{
  flightDetailsJson_["rid_details"]["id"]                      = this->flightDetails_.id; 
  flightDetailsJson_["rid_details"]["operator_id"]             =  this->flightDetails_.operator_id;  
  flightDetailsJson_["rid_details"]["operator_location"]       = {
                                                   {"lng",this->flightDetails_.operator_location_lng},
                                                   {"lat",this->flightDetails_.operator_location_lat}
                                                  };
  flightDetailsJson_["rid_details"]["operation_description"]   = this->flightDetails_.operation_description;
  
  //flightDetailsJson_["rid_details"]["auth_data"]               = {
  //                                                  {"format",  this->flightDetails_.auth_data_format}, 
  //                                                  {"data", this->flightDetails_.auth_data_data}
  //                                                };
  flightDetailsJson_["rid_details"]["serial_number"]           = this->flightDetails_.serial_number;
  flightDetailsJson_["rid_details"]["registration_number"]     = this->flightDetails_.registration_number;

  flightDetailsJson_["aircraft_type"]                          = this->flightDetails_.aircraft_type;
  flightDetailsJson_["operator_name"]                          = this->flightDetails_.operator_name;

}