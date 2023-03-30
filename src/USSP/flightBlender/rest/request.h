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
    ~Request();

    void sendHttp(http::request<http::string_body>& request);
    std::string receiveHttpResponse();

    std::string get(std::string target);
    std::string post(std::string target);
    std::string put(std::string target);

    void setBody(const std::string& body = "");

private:
    struct connection_params {
        const int http_version = 11;
        const std::string ip = "0.0.0.0";
        const std::string port = "8000";
        const std::string host = ip + ':' + port;
        const std::string authorization_token = "Bearer eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJmbGlnaHRibGVuZGVyLnRpaS5hZSIsImNsaWVudF9pZCI6InVzc19ub2F1dGgiLCJleHAiOjE2NzgzNjM0NTgsImlzcyI6Ik5vQXV0aCIsImp0aSI6ImY0ODA4NGU4LTM1NmItNDdmNC05NDFmLTMyOGM2Y2U4YTNiZSIsIm5iZiI6MTY3ODM1OTg1Nywic2NvcGUiOiJibGVuZGVyLnJlYWQiLCJzdWIiOiJ1c3Nfbm9hdXRoIn0.T6J6YHPLrRBIlLSMzZ1Rl_RbZM_GspxWrfFt-hUrRGawL-n5K6r3B6oijzKaBm386vAzsYsqJKptOC82BSVnRHz1jCNmwO0KSVhmtoTC_Va1JWOx-WDoWiAd2Xu-SmqqOvtne5-NAgnfzkYHWw4BRpoC3ky3ZYIhORffioqow5U";
        const std::string content_type = "application/json";
        const std::string accept =  "*/*";
        const std::string accept_encoding = "gzip, deflate, br";
        const std::string connection = "keep-alive";
    } connection_params_;

    net::io_service ioservice_;
    tcp::socket socket_;
    tcp::resolver resolver_;
    http::request<http::string_body> request_;

    std::mutex mutex_;

    void initHttpRequest();
};

}

#endif  // USSP_REQUEST_H_
