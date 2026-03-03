CXX = g++
PYTHON = python3
CXXFLAGS = -std=c++11 -O2 -Wall
TARGET = prog 
SRC = main.cpp
PLOT_SRC = plot.py
PLOT_CSV = "errors.csv"

all: $(TARGET) plot

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

plot: $(TARGET) $(PLOT_SRC)
	./$(TARGET)
	$(PYTHON) $(PLOT_SRC)	

clean:
	rm -f $(TARGET) $(DATA_FILE) *.pyc $(PLOT_CSV)


.PHONY: all plot clean
