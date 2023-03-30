// TII LICENSE Inlusion
#include "USSP/flightBlender/rest/client.h"

flightBlender::Client::Client()
{

}

std::string flightBlender::Client::SetFlightPlan(const std::string& body)
{
    request_.setBody(body);
    return request_.post("/flight_declaration_ops/set_flight_declaration");
}

std::string flightBlender::Client::RequestTelemetry(const std::string& body)
{
    request_.setBody(body);
    return request_.put("/flight_stream/set_telemetry");
}

std::string flightBlender::Client::Ping()
{
    request_.setBody("");
    return request_.get("/ping");
}
