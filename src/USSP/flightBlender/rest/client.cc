// TII LICENSE Inlusion
#include "USSP/flightBlender/rest/client.h"

flightBlender::Client::Client()
{

}

std::string flightBlender::Client::SetFlightPlan(const std::string& body)
{
    return request_.Post("/flight_declaration_ops/set_flight_declaration", body);
}

std::string flightBlender::Client::RequestTelemetry(const std::string& body)
{
    return request_.Put("/flight_stream/set_telemetry", body);
}

std::string flightBlender::Client::Ping()
{
    return request_.Get("/ping");
}
