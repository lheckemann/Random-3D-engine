CXX := g++
# Debug - set to -O2 only for releases.
CXXFLAGS := -g -Wall
LIBS := -lSDLmain -lSDL_image -lSDL $(shell pkg-config --libs glu)
CPPFLAGS := -I/usr/include/SDL -I/usr/include/GL

all: error.o timing.o logic.o draw.o defines.o
	g++ $(CXXFLAGS) -o main main.cpp $^ $(CPPFLAGS) $(LIBS)
	
%.o: %.cpp
	g++ $(CXXFLAGS) $(CPPFLAGS) $(LIBS) -c $< -o $@ 

clean:
	rm *.o

