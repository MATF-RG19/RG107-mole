PROGRAM = main.out
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter
#LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o image.o mole.o sargarepa.o rotkvica.o pecurka.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LDLIBS)

image.o: image.c image.h
	$(CXX) -c -o $@ $(CXXFLAGS) $< $(LDLIBS)

main.o: main.cpp image.c
	$(CXX) -c -o $@ $(CXXFLAGS) $< $(LDLIBS)

mole.o: mole.cpp mole.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $< $(LDLIBS)

sargarepa.o: sargarepa.cpp sargarepa.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $< $(LDLIBS)

rotkvica.o: rotkvica.cpp rotkvica.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $< $(LDLIBS)	

pecurka.o: pecurka.cpp pecurka.hpp
	$(CXX) -c -o $@ $(CXXFLAGS) $< $(LDLIBS)

.PHONY: clean run

clean:
	rm *.o $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)
