CXX = g++
CXXFLAGS = -std=c++11 -Wall

sources = main.cpp DigitCount.cpp UpperCaseCount.cpp SpaceCount.cpp
objs = $(sources:.cpp=.o)
exec = fileAnalyzer

all: $(exec)

$(exec): $(objs)
	$(CXX) $(CXXFLAGS) -o $(exec) $(objs)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	rm -f $(objs) $(exec)
