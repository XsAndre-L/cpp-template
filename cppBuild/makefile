CC = g++
CFLAGS = -std=c++11 -Wall

SRCDIR = src
BINDIR = build

SRC_FILES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SRC_FILES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

TARGET = myapp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*.o $(TARGET)
