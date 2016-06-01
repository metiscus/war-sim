CC=gcc
CFLAGS=-g -O0 -Wall -Wextra -MD
CXX=g++
CXXFLAGS=$(CFLAGS) -std=c++11 -Iexternal/rapidxml-1.13 -Iexternal/oolua-2.0.1/include -Iexternal/lua-5.3.2/include
CXXFLAGS+=-DDEBUG
LDDFLAGS=-L.

default: warsim

warsim_SRC=\
	src/main.cpp\
	src/country.cpp\
	src/factory.cpp\
	src/policy.cpp\
	src/recipe.cpp\
	src/resource.cpp\
	src/serializer.cpp\
	src/stockpile.cpp\
	src/territory.cpp\
	src/territorymanager.cpp\
	src/world.cpp\
	src/scriptbindings.cpp\
	src/render/camera.cpp\
	src/render/node.cpp\
	src/render/transform.cpp\
	src/render/vector.cpp\
	src/render/sprite.cpp\
	src/render/spritesheet.cpp\
	

warsim_OBJ=$(warsim_SRC:.cpp=.o)

warsim: $(warsim_OBJ) $(warsim_SRC) liboolua.a liblua5.a
	$(CXX) $(CXXFLAGS) -o warsim $(warsim_OBJ) $(LDDFLAGS) -loolua -llua5
	
include oolua.mk
include lua5.mk

clean:
	-rm -f warsim
	-find . -name "*.o" -exec rm {} \;
	-find . -name "*.d" -exec rm {} \;
	-rm -f liblua5.a liboolua.a

-include $(shell find -name "*.d")
