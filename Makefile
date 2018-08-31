#
ROOT_DIR=$(shell pwd)

TARGET		:= ds_test
LIBSRCPATH	:= $(ROOT_DIR)/ds_lib_src
OBJS_DIR	:= $(ROOT_DIR)/obj
CFLAG		:= -c -fPIC -I./include



SRC = ${wildcard $(LIBSRCPATH)/*.c}
OBJ = ${patsubst %.c, %.o, $(SRC)}

$(TARGET):check_dir $(OBJ)
	echo $(SRC) 
	echo $(OBJ)
	gcc $(CFLAG) test_main.c -o $@ 

$(OBJ):%.o:%.c
	gcc $(CFLAG) $^ -o $(OBJS_DIR)/$(notdir $@)
	gcc -shared -o libds.so $(OBJS_DIR)/$(notdir $@)

check_dir:
	-mkdir -p $(OBJS_DIR)

.PHONY:clean

clean:
	rm -rf $(TARGET) $(OBJS_DIR) libds.so




