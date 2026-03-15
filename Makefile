CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = banking

SRCS = main.cpp utils.cpp transaction.cpp account.cpp customer.cpp bank.cpp menu.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
