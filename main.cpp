#include "WebSocketHandler.h" 
#include "trader.h"
#include <iostream> 
#include <string>
#include "latency.h"

using namespace std;

const string CLIENT_ID = "Enter your client id here";
const string CLIENT_SECRET = "enter secret here";

void Execute(){
    try{
        WebSocketHandler websocket("test.deribit.com", "/ws/api/v2");
        websocket.connect();

        Executer trade(websocket);
        json auth_response = trade.authenticate(CLIENT_ID, CLIENT_SECRET);
        // std::cout << "Auth Response: " << auth_response.dump(4) << std::endl;

        while(true){
            std::cout << "\n--- Trading Menu ---\n";
            std::cout << "1. Place Order\n";
            std::cout << "2. Cancel Order\n";
            std::cout << "3. Modify Order\n";
            std::cout << "4. Get Order Book\n";
            std::cout << "5. View Current Positions\n";
            std::cout << "6. Exit\n";
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;

            auto total_time_start = Latency::start();


            if(choice == 6){
                std::cout << "Exiting...\n";
                break;
            }

            switch(choice){
                case 1: {
                    std:: string instrument_name;
                    double amount, price;
                    std::cout << "Enter instrument name (e.g., BTC-PERPETUAL): ";
                    std::cin >> instrument_name;
                    std::cout << "Enter amount: ";
                    std::cin >> amount;
                    std::cout << "Enter price: ";
                    std::cin >> price;

                    try{
                        auto buy_start = Latency::start();
                        json buy_response = trade.buyOrder(instrument_name, amount, price);
                        Latency::end(buy_start, "Place Time");
                        std::cout << "Order Response: " << buy_response.dump(4) << std::endl;
                    }
                    catch(const std::exception& e){
                        std::cerr << "Error placing order: " << e.what() << std::endl;
                    }
                    break;
                }
                case 2: {
                    std::string order_id;
                    std::cout << "Enter order ID to cancel: ";
                    std::cin >> order_id;

                    try{
                        auto cancel_start = Latency::start();
                        json cancel_response = trade.cancelOrder(order_id);
                        Latency::end(cancel_start, "Cancel Time");
                        std::cout << "Cancel Response: " << cancel_response.dump(4) << std::endl;
                    }
                    catch(const std::exception& e){
                        std::cerr << "Error cancelling order: " << e.what() << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::string order_id;
                    double amount, price;
                    std::cout << "Enter order ID to modify: ";
                    std::cin >> order_id;
                    std::cout << "Enter new price: ";
                    std::cin >> price;
                    std::cout << "Enter new amount: ";
                    std::cin >> amount;

                    try{
                        auto modify_start = Latency::start();
                        json modify_response = trade.modifyOrder(order_id, price, amount);
                        Latency::end(modify_start, "Modify Time");
                        std::cout << "Modify Response: " << modify_response.dump(4) << std::endl;
                    }
                    catch(const std::exception& e){
                        std::cerr << "Error modifying order: " << e.what() << std::endl;
                    }
                    break;
                }
                case 4: {
                    std::string instrument_name;
                    std::cout << "Enter instrument name to view order book (e.g., BTC-PERPETUAL): ";
                    std::cin >> instrument_name;

                    try{
                        auto order_book_start = Latency::start();
                        json order_book = trade.getOrderBook(instrument_name);
                        Latency::end(order_book_start, "Order Book Time");
                        std::cout << "Order Book: " << order_book.dump(4) << std::endl;
                    }
                    catch(const std::exception& e){
                        std::cerr << "Error getting order book: " << e.what() << std::endl;
                    }
                    break;
                }
                case 5: {
                    try{
                        auto positions_start = Latency::start();
                        json positions = trade.getPositions();
                        Latency::end(positions_start, "Positions Time");
                        std::cout << "Positions: " << positions.dump(4) << std::endl;
                    }
                    catch(const std::exception& e){
                        std::cerr << "Error getting positions: " << e.what() << std::endl;
                    }
                    break;
                }
                default:{
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
            Latency::end(total_time_start, "Total Time");
        }
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main(){
    try{
        Execute();
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}