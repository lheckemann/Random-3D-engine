CXX := g++
# Debug - set to -O2 only for releases.
CXXFLAGS := -g -Wall
LIBS := -lSDLmain -lSDL_image -lSDL
CPPFLAGS := -I/usr/include/SDL -I/usr/include/GL

all: error.o timing.o logic.o draw.o
	g++ $(CXXFLAGS) -o main main.cpp $^ $(CPPFLAGS) $(LIBS)
	
%.o: %.cpp
	g++ $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@ 

clean:
	rm *.o

