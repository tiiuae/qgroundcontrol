/****************************************************************************
 *
 * (c) 2023 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "UTMSPBlenderRestInterface.h"
#include "UTMSPProductJson.h"

UTMSPBlenderRestInterface::UTMSPBlenderRestInterface() :
    UTMSPRestInterface("")  // Initialize with an empty target URL
{
    initialize();  // Call the initialization function
}

void UTMSPBlenderRestInterface::initialize()
{
    // Parse the JSON file and set the target URL dynamically
    UTMSPProductJson utmspInfo;
    utmspInfo.parseJson("product.json");

    // Assuming "flight_authorization" is a key in the available services
    const std::string fpRequestUrlKey = "flight_authorization";
    const std::string nrIdRequestUrlKey = "network_remote_id";

    // Find the service with the specified keys
    auto fpServiceIt = std::find_if(
        utmspInfo.availableServices.begin(),
        utmspInfo.availableServices.end(),
        [fpRequestUrlKey](const QJsonObject& service) {
            return service.contains(QString::fromStdString(fpRequestUrlKey));
        }
    );

    auto nrIdServiceIt = std::find_if(
        utmspInfo.availableServices.begin(),
        utmspInfo.availableServices.end(),
        [nrIdRequestUrlKey](const QJsonObject& service) {
            return service.contains(QString::fromStdString(nrIdRequestUrlKey));
        }
    );

    if (fpServiceIt != utmspInfo.availableServices.end() &&
        nrIdServiceIt != utmspInfo.availableServices.end()) {
        // Extract the request URLs dynamically and set them as class members
        fpRequestUrl_ = fpServiceIt->value(fpRequestUrlKey.c_str()).toObject()["request_url"].toString().toStdString();
        nrIdRequestUrl_ = nrIdServiceIt->value(nrIdRequestUrlKey.c_str()).toObject()["telemetry_submit_url"].toString().toStdString();



        // Set the target URL for the UTMSPRestInterface base class
        UTMSPRestInterface(utmspInfo.baseUrl.toStdString());
    } else {
        // Handle error: the specified keys were not found in the available services
        // You might want to set default values or throw an exception depending on your error handling strategy
    }
}

std::pair<int, std::string> UTMSPBlenderRestInterface::setFlightPlan(const std::string& body)
{
    // Modify the request with the dynamically obtained target URL
    modifyRequest(fpRequestUrl_, http::verb::post, body);

    // Execute the request
    return executeRequest();
}

std::pair<int, std::string> UTMSPBlenderRestInterface::requestTelemetry(const std::string& body)
{
    // Modify the request with the dynamically obtained target URL
    modifyRequest(nrIdRequestUrl_, http::verb::put, body);

    // Execute the request
    return executeRequest();
}

std::pair<int, std::string> UTMSPBlenderRestInterface::ping()
{
    const std::string target = "/ping";
    modifyRequest(target, http::verb::get);

    return executeRequest();
}
