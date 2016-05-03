CXX=g++
CXXFLAGS=-g -O3 -Wall -Wextra -MD -std=c++11 -lboost_serialization
CXXFLAGS+=-DDEBUG

default: warsim

warsim_SRC=\
	main.cpp\
	country.cpp\
	factory.cpp\
	policy.cpp\
	recipe.cpp\
	stockpile.cpp\
	territory.cpp\
	world.cpp\
	

warsim_OBJ=$(warsim_SRC:.cpp=.o)

warsim: $(warsim_OBJ) $(warsim_SRC)
	$(CXX) $(CXXFLAGS) -o warsim $(warsim_OBJ)

clean:
	-rm -f *.o *.d warsim

-include *.d