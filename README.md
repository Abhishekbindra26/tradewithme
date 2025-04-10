# Trading Application - GoQuant

## Overview

GoQuant is a high-performance C++ trading application that interfaces with WebSocket-based trading APIs. The application provides comprehensive trading functionalities including user authentication, order management, real-time order book data retrieval, and position monitoring. A key feature is the built-in latency tracking system that measures and reports the execution times of critical operations.

## Features

- **Secure WebSocket Communication**: Establishes and maintains secure connections with trading platforms using TLS encryption
- **Comprehensive Trading Operations**: Place, modify, and cancel orders with ease
- **Real-time Market Data**: Access live order book information for any supported instrument
- **Position Management**: View and track your current trading positions
- **Performance Monitoring**: Built-in latency tracking for all critical operations
- **User-friendly Interface**: Intuitive command-line menu for executing trading actions

## File Structure and Purpose

### Primary Files

#### latency.h and latency.cpp
These files define and implement the Latency class, which measures and reports the execution times of critical operations. This functionality is pivotal for monitoring performance and identifying bottlenecks, aiding in application optimization.

#### WebSocketHandler.h and WebSocketHandler.cpp
Responsible for managing WebSocket communication with the trading platform. These files handle establishing secure connections, exchanging JSON messages, and ensuring data encryption using TLS.

#### trader.h and trader.cpp
Encapsulate the core trading logic in the Executer class. This includes tasks such as authenticating users, managing orders, and retrieving market data, forming the backbone of trading operations.

#### main.cpp
This serves as the application's entry point. It orchestrates user interactions, integrates modules, and provides latency tracking for performance insights, offering a cohesive user experience.

### Supporting Files
- **makefile**: Configures the build environment to compile the application efficiently
- **README.md**: Provides an overview of the project, setup instructions, and a user guide
- **Dependencies**: Includes key libraries such as Boost for WebSocket communication and nlohmann::json for JSON data handling

## Components

### 1. Latency Measurement (latency.h and latency.cpp)

#### Description
The Latency class is designed to monitor and report the execution times of key operations within the application.

#### Key Methods
- `start()`: Captures the current system time as a reference point for measuring latency
- `end(start_time, action_name)`: Computes the elapsed time since start_time and outputs it along with the specified action_name

#### Features
- Granular Insights: Captures detailed timing for each operation
- Formatted Outputs: Produces human-readable results for use in performance analytics
- Integration Ready: Easily integrates with other modules for real-time performance tracking

### 2. WebSocket Handler (WebSocketHandler.h and WebSocketHandler.cpp)

#### Description
The WebSocketHandler class manages secure WebSocket communication with the trading platform, handling both outgoing and incoming messages.

#### Key Methods
- `connect()`: Initiates and authenticates a secure connection to the WebSocket server
- `sendMessage(json message)`: Encodes and transmits JSON-formatted requests
- `readMessage()`: Receives and decodes server responses
- `close()`: Gracefully terminates the WebSocket connection
- `onMessage(std::string message)`: Processes incoming messages in real time

#### Constructor
- `WebSocketHandler(const std::string& host, const std::string& endpoint)`: Establishes the WebSocket session with a specified server host and endpoint

#### Additional Features
- TLS Encryption: Ensures secure communication
- Error Handling: Includes robust handling for connection issues and data parsing errors
- Real-Time Processing: Efficiently manages incoming market data streams

### 3. Trading Executor (trader.h and trader.cpp)

#### Description
The Executer class encapsulates all trading functionalities and provides an interface for API interactions.

#### Key Methods
- `authenticate(client_id, client_secret)`: Logs the user into the API and retrieves an authentication token
- `buyorder(instrument_name, amount, price)`: Submits a limit buy order for the specified instrument
- `cancelorder(order_id)`: Cancels an order identified by its unique order_id
- `modifyorder(order_id, new_price, new_amount)`: Updates existing order parameters
- `getOrderBook(instrument_name)`: Retrieves live order book details for a specific instrument
- `getPositions()`: Fetches an overview of the user's current positions

#### Helper Methods
- `getNextRequestId()`: Generates unique IDs for API requests, aiding in tracking and debugging

#### Design Highlights
- Encapsulation: Cleanly separates API logic from other application modules
- Error Resilience: Proactively addresses potential issues like invalid parameters and connection timeouts
- Scalability: Designed to support additional API features with minimal changes

### 4. Main Application (main.cpp)

#### Description
The main.cpp file orchestrates all interactions between users, APIs, and the application's modules.

#### Features
- Authentication Workflow: Guides users to authenticate seamlessly
- Interactive Menu: Offers an intuitive interface for selecting trading operations
- Integrated Latency Tracking: Uses the Latency class to monitor and report operation performance

#### Execution Workflow
1. Initialization: Configures and initializes WebSocket and API connections
2. User Authentication: Authenticates credentials using Executer::authenticate
3. Action Menu: Presents a user-friendly menu for trading actions
4. Performance Insights: Measures and displays latency for each user action

## Dependencies
- **Boost Libraries**: Powers WebSocket communication and SSL encryption
- **nlohmann::json**: Simplifies JSON parsing and serialization
- **C++ Standard Library**: Utilized for essential tasks like time management and string handling

## Build Instructions

### Requirements
- A C++17-compliant compiler (e.g., GCC, Clang)
- Installed Boost libraries
- CMake for build configuration

### Steps
1. Clone the repository:
   ```
   git clone https://github.com/Abhishekbindra26/tradewithme.git
   cd tradewithme
   ```

2. Compile the application:
   ```
   make
   ```

3. Launch the executable:
   ```
   ./bin
   ```

## Sample Usage
1. Start the application
2. Authenticate using CLIENT_ID and CLIENT_SECRET
3. Select an action (e.g., "Place Buy Order" or "Cancel Order") from the menu
4. View operation results, including latency metrics, in the output

## Error Handling
- Connection Failures: Reconnects automatically and logs errors to stderr
- Invalid Inputs: Provides clear prompts for corrections
- API Response Errors: Displays user-friendly messages for debugging purposes

## Future Enhancements
- Dynamic Reconnection: Automatically restore WebSocket sessions during interruptions
- Comprehensive Logging: Add detailed logs for error analysis and audit trails
- Visualization Dashboards: Introduce real-time dashboards for latency and performance metrics

