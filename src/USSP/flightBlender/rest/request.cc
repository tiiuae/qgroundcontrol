// TII LICENSE Inlusion
#include "USSP/flightBlender/rest/request.h"
#include <fstream>
#include <iostream>

flightBlender::Request::Request() : socket_(ioservice_), resolver_(ioservice_)
{
    boost::asio::ip::tcp::resolver::query query("0.0.0.0", "8000");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver_.resolve(query);

    boost::asio::connect(socket_, endpoint_iterator);
}

template<typename T>
void print(http::request<T>& request)
{
    std::ostringstream oss;
    oss <<"Request message " << request;
    std::cout << oss.str() << std::endl;
    oss.clear();
}

http::request<http::string_body> flightBlender::Request::CreateHttpRequest(std::string target, http::verb method, const std::string& body)
{
    http::request<http::string_body> request;

    request.target(target);
    request.method(method);

    if (body.size())
    {
        request.body() = body;
        request.prepare_payload();
        request.set(http::field::content_length, body.length());
    }

    request.version(11);
    auto const host = "0.0.0.0:8000";
    request.set(http::field::host, host);

    request.set(http::field::authorization, "Bearer eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJmbGlnaHRibGVuZGVyLnRpaS5hZSIsImNsaWVudF9pZCI6InVzc19ub2F1dGgiLCJleHAiOjE2NzgzNjM0NTgsImlzcyI6Ik5vQXV0aCIsImp0aSI6ImY0ODA4NGU4LTM1NmItNDdmNC05NDFmLTMyOGM2Y2U4YTNiZSIsIm5iZiI6MTY3ODM1OTg1Nywic2NvcGUiOiJibGVuZGVyLnJlYWQiLCJzdWIiOiJ1c3Nfbm9hdXRoIn0.T6J6YHPLrRBIlLSMzZ1Rl_RbZM_GspxWrfFt-hUrRGawL-n5K6r3B6oijzKaBm386vAzsYsqJKptOC82BSVnRHz1jCNmwO0KSVhmtoTC_Va1JWOx-WDoWiAd2Xu-SmqqOvtne5-NAgnfzkYHWw4BRpoC3ky3ZYIhORffioqow5U");
    request.set(http::field::content_type, "application/json");

    request.set(http::field::accept, "*/*");
    request.set(http::field::accept_encoding, "gzip, deflate, br");
    request.set(http::field::connection, "keep-alive");

    return request;
}

std::string flightBlender::Request::ReceiveHttpResponse()
{
    beast::flat_buffer buffer;
    http::response<http::dynamic_body> response;
    response.version(11);
    http::read(socket_, buffer, response);

    return boost::beast::buffers_to_string(response.body().data());
}

void flightBlender::Request::SendHttp(http::request<http::string_body>& request)
{
    if( !socket_.is_open() )
        socket_.open(boost::asio::ip::tcp::v4());

    //print(request);

    // send HTTP request
    http::write(socket_, request);
}

std::string flightBlender::Request::Get(std::string target, const std::string& body)
{
    auto request = CreateHttpRequest(target, http::verb::get, body);
    SendHttp(request);

    return ReceiveHttpResponse();
}

std::string flightBlender::Request::Post(std::string target, const std::string& body)
{
    auto request = CreateHttpRequest(target, http::verb::post, body);
    SendHttp(request);

    return ReceiveHttpResponse();
}

std::string flightBlender::Request::Put(std::string target, const std::string& body)
{
    auto request = CreateHttpRequest(target, http::verb::put, body);
    SendHttp(request);

    return ReceiveHttpResponse();
}
