// TII LICENSE Inlusion
#pragma once
#ifndef USSP_CLIENT_H_
#define USSP_CLIENT_H_

#include "request.h"

namespace flightBlender {

class Client
{
public:
    Client();

    std::string SetFlightPlan(const std::string& body);
    std::string RequestTelemetry(const std::string& body);
    std::string Ping();

private:
    Request request_;
};
}

#endif  // USSP_CLIENT_H_
