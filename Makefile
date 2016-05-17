CC=gcc
CFLAGS=-g -O0 -Wall -Wextra -MD
CXX=g++
CXXFLAGS=$(CFLAGS) -std=c++11 -Irapidxml-1.13 -Ioolua-2.0.1/include -Ilua-5.3.2/include
CXXFLAGS+=-DDEBUG
LDDFLAGS=-L.

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

warsim: $(warsim_OBJ) $(warsim_SRC) liboolua.a liblua5.a
	$(CXX) $(CXXFLAGS) -o warsim $(warsim_OBJ) $(LDDFLAGS) -loolua -llua5
	
include oolua.mk
include lua5.mk
	
parser: ddf.lpp ddf.ypp
	flex ddf.lpp
	bison -W ddf.ypp
	$(CC) $(CFLAGS) -c lex.yy.c
	$(CXX) $(CXXFLAGS) -o parser lex.yy.o ddf.tab.cpp
clean:
	-rm -f warsim
	-find . -name "*.o" -exec rm {} \;
	-find . -name "*.d" -exec rm {} \;
	-rm -f ddf.tab.c ddf.tab.h parser ddf.tab.cpp ddf.tab.hpp
	-rm -f liblua5.a liboolua.a

-include $(shell find -name "*.d")
