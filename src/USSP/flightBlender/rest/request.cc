// TII LICENSE Inlusion
#include "USSP/flightBlender/rest/request.h"
#include <fstream>
#include <iostream>

flightBlender::Request::Request() : socket_(ioservice_), resolver_(ioservice_)
{
    boost::asio::ip::tcp::resolver::query query("0.0.0.0", "8000");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver_.resolve(query);

    boost::asio::connect(socket_, endpoint_iterator);
    initHttpRequest();
}

flightBlender::Request::~Request()
{
    socket_.close();
    ioservice_.stop();
}

template<typename T>
void print(http::request<T>& request)
{
    std::ostringstream oss;
    oss <<"Request message " << request;
    std::cout << oss.str() << std::endl;
    oss.clear();
}

void flightBlender::Request::initHttpRequest()
{
    request_.set(http::field::content_length, 0);

    request_.version(connection_params_.http_version);
    request_.set(http::field::host, connection_params_.host);

    request_.set(http::field::authorization, connection_params_.authorization_token);
    request_.set(http::field::content_type, connection_params_.content_type);

    request_.set(http::field::accept, connection_params_.accept);
    request_.set(http::field::accept_encoding, connection_params_.accept_encoding);
    request_.set(http::field::connection, connection_params_.connection);
}

std::string flightBlender::Request::receiveHttpResponse()
{
    beast::flat_buffer buffer;
    http::response<http::dynamic_body> response;
    response.version(connection_params_.http_version);
    http::read(socket_, buffer, response);

    if (response.body().size() == 0)
        return "";

    return boost::beast::buffers_to_string(response.body().data());
}

void flightBlender::Request::sendHttp(http::request<http::string_body>& request)
{
    if( !socket_.is_open() )
        socket_.open(boost::asio::ip::tcp::v4());

    //print(request);

    // send HTTP request
    std::lock_guard<std::mutex> lock_guard(mutex_);
    http::write(socket_, request_);
}

std::string flightBlender::Request::get(std::string target)
{
    request_.target(target);
    request_.method(http::verb::get);

    sendHttp(request_);

    return receiveHttpResponse();
}

std::string flightBlender::Request::post(std::string target)
{
    request_.target(target);
    request_.method(http::verb::post);

    sendHttp(request_);

    return receiveHttpResponse();
}

std::string flightBlender::Request::put(std::string target)
{
    request_.target(target);
    request_.method(http::verb::put);

    sendHttp(request_);

    return receiveHttpResponse();
}

void flightBlender::Request::setBody(const std::string& body)
{
    if (body.empty())
        return;

    request_.body() = body;
    request_.prepare_payload();
    request_.set(http::field::content_length, body.length());
}
