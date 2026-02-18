CXX = g++
CXXFLAGS = -I./include -Wall -std=c++11
TARGET = prog
SOURCES = $(wildcard src/*.cpp)
DATA_DIR = data
PLOTS_DIR = plots

$(TARGET): $(SOURCES) | $(DATA_DIR) $(PLOTS_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

$(PLOTS_DIR):
	mkdir -p $(PLOTS_DIR)

clean:
	rm -f $(TARGET)
	rm -rf $(DATA_DIR)
	rm -rf $(PLOTS_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
