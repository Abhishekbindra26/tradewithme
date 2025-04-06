#include "trader.h"
#include <iostream>
#include "latency.h"

std::atomic<int> Executer::request_id{ 1 };
Executer::Executer(WebSocketHandler& websocket)
    : websocket_(websocket) {}

int Executer::getNextRequestId() {
    return request_id++;
}


json Executer::authenticate(const std::string& client_id, const std::string& client_secret){
    try{
        json authMessage = {
            {"jsonrpc", "2.0"},
            {"id", getNextRequestId()},
            {"method", "public/auth"},
            {"params", {
                {"grant_type", "client_credentials"},
                {"client_id", client_id},
                {"client_secret", client_secret}
            }}
        };
        websocket_.sendMessage(authMessage);
        auto response = websocket_.readMessage();

        if(!response.contains("result")){
            throw std::runtime_error("Authentication failed: " + response.dump());
        }
        return response["result"];

    }
    catch(const std::exception& e){
        std::cerr << "Error in authentication: " << e.what() << std::endl;
        throw;
    }
}

json Executer::buyOrder(const std::string& instrument_name, double amount, double price){
    try{
        json buyRequest = {
            {"jsonrpc", "2.0"},
            {"id", getNextRequestId()},
            {"method", "private/buy"},
            {"params", {
                {"instrument_name", instrument_name},
                {"amount", amount},
                {"type", "limit"},
                {"price", price}
            }}
        };
        websocket_.sendMessage(buyRequest);
        return websocket_.readMessage();
    }
    catch(const std::exception& e){
        std::cerr << "Error in buy: " << e.what() << std::endl;
        throw;
    }
}

json Executer::cancelOrder(const std::string& order_id){
    try{
        json cancel_req = {
            {"jsonrpc", "2.0"},
            {"id", getNextRequestId()},
            {"method", "private/cancel"},
            {"params", {{"order_id", order_id}}}
        };
        websocket_.sendMessage(cancel_req);
        return websocket_.readMessage();
    }
    catch(const std::exception& e){
        std::cerr << "Error in cancel: " << e.what() << std::endl;
        throw;
    }
}

json Executer::modifyOrder(const std::string& order_id, double new_price, double new_amount){
    try{
        json modify_req = {
            {"jsonrpc", "2.0"},
            {"id", getNextRequestId()},
            {"method", "private/edit"},
            {"params", {
                {"order_id", order_id},
                {"new_price", new_price},
                {"new_amount", new_amount},
                {"contracts", new_amount}
            }}
        };
        websocket_.sendMessage(modify_req);
        return websocket_.readMessage();
    }
    catch(const std::exception& e){
        std::cerr << "Error in modify: " << e.what() << std::endl;
        throw;
    }
}

json Executer::getOrderBook(const std::string& instrument_name){
    try {
        json request = {
            {"jsonrpc", "2.0"},
            {"id", getNextRequestId()},
            {"method", "public/get_order_book"},
            {"params", {{"instrument_name", instrument_name}}}
        };
        websocket_.sendMessage(request);
        return websocket_.readMessage();
    }
    catch (const std::exception& e) {
        std::cerr << "Error in getOrderBook: " << e.what() << std::endl;
        throw;
    }
}

json Executer::getPositions(){
    try {
        json request = {
            {"jsonrpc", "2.0"},
            {"id", getNextRequestId()},
            {"method", "private/get_positions"},
            {"params", {}}
        };
        websocket_.sendMessage(request);
        return websocket_.readMessage();
    }
    catch (const std::exception& e) {
        std::cerr << "Error in getPositions: " << e.what() << std::endl;
        throw;
    }
}