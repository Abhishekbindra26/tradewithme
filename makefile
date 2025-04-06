CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

LIBS = -lboost_system -lssl -lcrypto 

TARGET = bin

SRC = main.cpp WebSocketHandler.cpp trader.cpp latency.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
