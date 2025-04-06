#include "WebSocketHandler.h"
#include <iostream>

WebSocketHandler::WebSocketHandler(const std::string& host, const std::string& endpoint)
    : sslCtx(ssl::context::tlsv12_client),
    resolver(ctx),
    ws(ctx, sslCtx),
    host(host),
    endPoint(endpoint) {
        sslCtx.set_default_verify_paths();
    };


void WebSocketHandler::connect(){
    try{
        auto const results = resolver.resolve(host, "443");
        asio::connect(ws.next_layer().next_layer(), results.begin(), results.end());
        ws.next_layer().handshake(ssl::stream_base::client);
        ws.handshake(host, endPoint);
        std::cout << "WebSocket connected successfully!" << std::endl;
    }   
    catch(const std::exception& e){
        std::cerr << "Error during WebSocket connection: " << e.what() << std::endl;
    }
}

void WebSocketHandler::onMessage(const std::string& message){
    json data = json::parse(message);
}

void WebSocketHandler::sendMessage(const json& message){
    try{
        std::string message_str = message.dump();
        ws.write(asio::buffer(message_str));
        // std::cout << "Sent message: " << message_str << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "Error sending message: " << e.what() << std::endl;
    }
}

json WebSocketHandler::readMessage(){
    try{
        beast::flat_buffer buffer;
        ws.read(buffer);
        std::string message_str = beast::buffers_to_string(buffer.data());
        // std::cout << "Received message: " << message_str << std::endl;

        return json::parse(message_str);
    }
    catch(const std::exception& e){
        std::cerr << "Error reading message: " << e.what() << std::endl;
        throw;
    }
}

void WebSocketHandler::close(){
    try{
        ws.close(beast::websocket::close_code::normal);
        std::cout << "WebSocket closed successfully!" << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << "Error closing WebSocket: " << e.what() << std::endl;
    }
}