CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall -Wextra

LIBRARY_NAME = LogLibrary
APP = LogApp
LIBRARY_SRC = LogLibrary.cpp
APP_SRC = LogApp.cpp
LIB = libLogLibrary.so

all: $(LIB) $(APP)

$(LIBRARY_NAME).o: $(LIBRARY_SRC)
	$(CXX) -fPIC $(CXXFLAGS) -c $< -o $@

$(APP).o: $(APP_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB): $(LIBRARY_NAME).o
	$(CXX) -shared -o $@ $^

$(APP): $(APP).o $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^ -L. -l$(LIBRARY_NAME)

clean:
	rm -f $(LIB) $(APP) $(LIBRARY_NAME).o $(APP).o

.PHONY: all clean