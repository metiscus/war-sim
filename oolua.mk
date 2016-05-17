oolua_SRC=\
    oolua-2.0.1/src/class_from_stack.cpp\
    oolua-2.0.1/src/oolua_push.cpp\
    oolua-2.0.1/src/oolua_check_result.cpp\
    oolua-2.0.1/src/oolua_ref.cpp\
    oolua-2.0.1/src/oolua_chunk.cpp\
    oolua-2.0.1/src/oolua_registration.cpp\
    oolua-2.0.1/src/oolua.cpp\
    oolua-2.0.1/src/oolua_script.cpp\
    oolua-2.0.1/src/oolua_error.cpp\
    oolua-2.0.1/src/oolua_stack_dump.cpp\
    oolua-2.0.1/src/oolua_exception.cpp\
    oolua-2.0.1/src/oolua_string.cpp\
    oolua-2.0.1/src/oolua_function.cpp\
    oolua-2.0.1/src/oolua_table.cpp\
    oolua-2.0.1/src/oolua_helpers.cpp\
    oolua-2.0.1/src/proxy_storage.cpp\
    oolua-2.0.1/src/oolua_open.cpp\
    oolua-2.0.1/src/push_pointer_internal.cpp\
    oolua-2.0.1/src/oolua_pull.cpp\
    oolua-2.0.1/src/stack_get.cpp\

oolua_OBJ=$(oolua_SRC:.cpp=.o)
    
liboolua.a: $(oolua_OBJ)
	ar -rcs liboolua.a $(oolua_OBJ)