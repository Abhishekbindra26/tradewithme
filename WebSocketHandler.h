#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <string>
#include <boost/beast.hpp>
#include "../json/single_include/nlohmann/json.hpp"

namespace asio = boost::asio;
namespace ssl = asio::ssl;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;
using json = nlohmann::json;

class WebSocketHandler{
public:
    WebSocketHandler(const std::string& host, const std::string& endpoint);

    void onMessage(const std::string& message);
    void connect();
    void sendMessage(const json& message);
    json readMessage();
    void close();

private:
    asio::io_context ctx;
    ssl::context sslCtx;
    tcp::resolver resolver;
    beast::websocket::stream<ssl::stream<tcp::socket>> ws;
    std::string host;
    std::string endPoint;
};