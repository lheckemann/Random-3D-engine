CXX := g++
# Debug - set to -O2 only for releases.
CXXFLAGS := -g -Wall
LIBS := -lSDLmain -lSDL_image -lSDL $(shell pkg-config --libs glu)
CPPFLAGS := -I/usr/include/SDL -I/usr/include/GL

engine: error.o timing.o defines.o
	g++ $(CXXFLAGS) -o main main.cpp $^ $(CPPFLAGS) $(LIBS)

game: defines.o
	g++ $(CXXFLAGS) -o game.so game.cpp $^ -shared $(CPPFLAGS) $(LIBS) -fPIC

%.o: %.cpp
	g++ $(CXXFLAGS) $(CPPFLAGS) $(LIBS) -c $< -o $@ 

clean:
	rm *.o

