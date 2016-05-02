CXX=g++
CXXFLAGS=-g -O0 -Wall -Wextra -MD -std=c++11 -lboost_serialization

default: warsim

warsim_SRC=\
	main.cpp\
	stockpile.cpp\
	recipe.cpp

warsim_OBJ=$(warsim_SRC:.cpp=.o)

warsim: $(warsim_OBJ) $(warsim_SRC)
	$(CXX) $(CXXFLAGS) -o warsim $(warsim_OBJ)

clean:
	-rm -f *.o *.d warsim

-include *.d