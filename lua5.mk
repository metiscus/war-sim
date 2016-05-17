lua5_OBJ=\
	lua-5.3.2/src/lapi.o\
	lua-5.3.2/src/lcode.o\
	lua-5.3.2/src/lctype.o\
	lua-5.3.2/src/ldebug.o\
	lua-5.3.2/src/ldo.o\
	lua-5.3.2/src/ldump.o\
	lua-5.3.2/src/lfunc.o\
	lua-5.3.2/src/lgc.o\
	lua-5.3.2/src/llex.o\
	lua-5.3.2/src/lmem.o\
	lua-5.3.2/src/lobject.o\
	lua-5.3.2/src/lopcodes.o\
	lua-5.3.2/src/lparser.o\
	lua-5.3.2/src/lstate.o\
	lua-5.3.2/src/lstring.o\
	lua-5.3.2/src/ltable.o\
	lua-5.3.2/src/ltm.o\
	lua-5.3.2/src/lundump.o\
	lua-5.3.2/src/lvm.o\
	lua-5.3.2/src/lzio.o\
	lua-5.3.2/src/lauxlib.o\
	lua-5.3.2/src/lbaselib.o\
	lua-5.3.2/src/lbitlib.o\
	lua-5.3.2/src/lcorolib.o\
	lua-5.3.2/src/ldblib.o\
	lua-5.3.2/src/liolib.o\
	lua-5.3.2/src/lmathlib.o\
	lua-5.3.2/src/loslib.o\
	lua-5.3.2/src/lstrlib.o\
	lua-5.3.2/src/ltablib.o\
	lua-5.3.2/src/lutf8lib.o\
	lua-5.3.2/src/loadlib.o\
	lua-5.3.2/src/linit.o\

liblua5.a: $(lua5_OBJ)
	ar -rcs liblua5.a $(lua5_OBJ)