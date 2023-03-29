// TII LICENSE Inlusion
#pragma once
#ifndef USSP_REQUEST_H_
#define USSP_REQUEST_H_

#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace flightBlender {
class Request
{
public:
    Request();

    void SendHttp(http::request<http::string_body>& request);
    std::string ReceiveHttpResponse();
    http::request<http::string_body> CreateHttpRequest(std::string target, http::verb method, const std::string& body = "");

    std::string Get(std::string target, const std::string& body = "");
    std::string Post(std::string target, const std::string& body = "");
    std::string Put(std::string target, const std::string& body = "");

    std::string SetFlightPlan(const std::string& body);
    std::string RequestTelemetry(const std::string& body);
    std::string Ping();

private:
    net::io_service ioservice_;
    tcp::socket socket_;
    tcp::resolver resolver_;
};

}

#endif  // USSP_REQUEST_H_
