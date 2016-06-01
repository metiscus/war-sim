lua5_OBJ=\
	external/lua-5.3.2/src/lapi.o\
	external/lua-5.3.2/src/lcode.o\
	external/lua-5.3.2/src/lctype.o\
	external/lua-5.3.2/src/ldebug.o\
	external/lua-5.3.2/src/ldo.o\
	external/lua-5.3.2/src/ldump.o\
	external/lua-5.3.2/src/lfunc.o\
	external/lua-5.3.2/src/lgc.o\
	external/lua-5.3.2/src/llex.o\
	external/lua-5.3.2/src/lmem.o\
	external/lua-5.3.2/src/lobject.o\
	external/lua-5.3.2/src/lopcodes.o\
	external/lua-5.3.2/src/lparser.o\
	external/lua-5.3.2/src/lstate.o\
	external/lua-5.3.2/src/lstring.o\
	external/lua-5.3.2/src/ltable.o\
	external/lua-5.3.2/src/ltm.o\
	external/lua-5.3.2/src/lundump.o\
	external/lua-5.3.2/src/lvm.o\
	external/lua-5.3.2/src/lzio.o\
	external/lua-5.3.2/src/lauxlib.o\
	external/lua-5.3.2/src/lbaselib.o\
	external/lua-5.3.2/src/lbitlib.o\
	external/lua-5.3.2/src/lcorolib.o\
	external/lua-5.3.2/src/ldblib.o\
	external/lua-5.3.2/src/liolib.o\
	external/lua-5.3.2/src/lmathlib.o\
	external/lua-5.3.2/src/loslib.o\
	external/lua-5.3.2/src/lstrlib.o\
	external/lua-5.3.2/src/ltablib.o\
	external/lua-5.3.2/src/lutf8lib.o\
	external/lua-5.3.2/src/loadlib.o\
	external/lua-5.3.2/src/linit.o\

liblua5.a: $(lua5_OBJ)
	ar -rcs liblua5.a $(lua5_OBJ)
