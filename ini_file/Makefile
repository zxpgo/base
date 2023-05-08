CC = g++
CFLAGS = -g

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET=test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$.o: %.cpp
	$(CC) %(CFLAGS -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)
