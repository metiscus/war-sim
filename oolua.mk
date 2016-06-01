CXXFLAGS+= -DOOLUA_NEW_POINTER_DEFAULT_IS_SHARED_TYPE=1 -DOOLUA_USE_SHARED_PTR=1

oolua_SRC=\
    external/oolua-2.0.1/src/class_from_stack.cpp\
    external/oolua-2.0.1/src/oolua_push.cpp\
    external/oolua-2.0.1/src/oolua_check_result.cpp\
    external/oolua-2.0.1/src/oolua_ref.cpp\
    external/oolua-2.0.1/src/oolua_chunk.cpp\
    external/oolua-2.0.1/src/oolua_registration.cpp\
    external/oolua-2.0.1/src/oolua.cpp\
    external/oolua-2.0.1/src/oolua_script.cpp\
    external/oolua-2.0.1/src/oolua_error.cpp\
    external/oolua-2.0.1/src/oolua_stack_dump.cpp\
    external/oolua-2.0.1/src/oolua_exception.cpp\
    external/oolua-2.0.1/src/oolua_string.cpp\
    external/oolua-2.0.1/src/oolua_function.cpp\
    external/oolua-2.0.1/src/oolua_table.cpp\
    external/oolua-2.0.1/src/oolua_helpers.cpp\
    external/oolua-2.0.1/src/proxy_storage.cpp\
    external/oolua-2.0.1/src/oolua_open.cpp\
    external/oolua-2.0.1/src/push_pointer_internal.cpp\
    external/oolua-2.0.1/src/oolua_pull.cpp\
    external/oolua-2.0.1/src/stack_get.cpp\

oolua_OBJ=$(oolua_SRC:.cpp=.o)

liboolua.a: $(oolua_OBJ)
	ar -rcs liboolua.a $(oolua_OBJ)
