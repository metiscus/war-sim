CC=gcc
CFLAGS=-g -O0 -Wall -Wextra -MD
CXX=g++
CXXFLAGS=$(CFLAGS) -std=c++11 -lboost_serialization -Irapidxml-1.13
CXXFLAGS+=-DDEBUG

default: warsim

warsim_SRC=\
	main.cpp\
	country.cpp\
	factory.cpp\
	policy.cpp\
	recipe.cpp\
	resource.cpp\
	serializer.cpp\
	stockpile.cpp\
	territory.cpp\
	world.cpp\
	

warsim_OBJ=$(warsim_SRC:.cpp=.o)

warsim: $(warsim_OBJ) $(warsim_SRC)
	$(CXX) $(CXXFLAGS) -o warsim $(warsim_OBJ)

	
parser: ddf.lpp ddf.ypp
	flex ddf.lpp
	bison -W ddf.ypp
	$(CC) $(CFLAGS) -c lex.yy.c
	$(CXX) $(CXXFLAGS) -o parser lex.yy.o ddf.tab.cpp
clean:
	-rm -f *.o *.d warsim
	-rm -f ddf.tab.c ddf.tab.h parser ddf.tab.cpp ddf.tab.hpp

-include *.d
