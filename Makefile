#
ROOT_DIR=$(shell pwd)

TARGET		:= ds_test
LIBSRCPATH	:= $(ROOT_DIR)/ds_lib_src
OBJS_DIR	:= $(ROOT_DIR)/obj

C_INCLUDE_PATH	+= $(ROOT_DIR)/include
LIBRARY_PATH 	+= $(ROOT_DIR)/../../lib

CFLAG		:= -lds -g3
C_LIB_FLAG	:= -c -fPIC -g3

SRC = ${wildcard $(LIBSRCPATH)/*.c}
OBJ = ${patsubst %.c, %.o, $(SRC)}

$(TARGET):check_dir $(OBJ)
	echo $(SRC) 
	echo $(OBJ)
	gcc -shared -o libds.so $(OBJS_DIR)/*.o
	@cp -arf libds.so $(LIBRARY_PATH)
	gcc test_main.c -o $@ $(CFLAG) -L$(LIBRARY_PATH) -I$(C_INCLUDE_PATH)

$(OBJ):%.o:%.c
	gcc $(C_LIB_FLAG) -I$(C_INCLUDE_PATH) $^ -o $(OBJS_DIR)/$(notdir $@)

check_dir:
	-mkdir -p $(LIBRARY_PATH) 
	-mkdir -p $(OBJS_DIR)

.PHONY:clean

clean:
	rm -rf $(TARGET) $(OBJS_DIR) libds.so 




