#pragma once
#include "WebSocketHandler.h"
#include "../json/single_include/nlohmann/json.hpp"
#include <string>

using json = nlohmann::json;

class Executer{
public:
    explicit Executer(WebSocketHandler& websocket);

    json authenticate(const std::string& client_id, const std::string& client_secret);
    json buyOrder(const std::string& instrument_name, double amount, double price);
    json cancelOrder(const std::string& order_id);
    json modifyOrder(const std::string& order_id, double new_price, double new_amount);
    json getOrderBook(const std::string& instrument_name);
    json getPositions();

private:
    WebSocketHandler& websocket_;
    static std::atomic<int> request_id;
    int getNextRequestId();
};