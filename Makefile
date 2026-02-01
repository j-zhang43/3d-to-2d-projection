# Define variables
CXX = g++
CXXFLAGS = -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic
EXECUTABLE = projection
SOURCES = projection.cpp

debug: CXXFLAGS += -g3 -DDEBUG -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)_debug
.PHONY: debug

release: CXXFLAGS += -O3 -DNDEBUG
release: $(EXECUTABLE)
.PHONY: release

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all

clean:
	rm -Rf *.dSYM
	rm -f $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE)_debug
.PHONY: clean