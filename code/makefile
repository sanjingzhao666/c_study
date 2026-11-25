
# 指定要生成的目标文件的名字
TARGET:= main

# 指定编译工具链 gcc / arm-linux-gcc / g++ / ...
CC:= arm-linux-gcc

# CSRCS 保存工程中所有的.c源文件的名字列表
# 1.c  2.c  3.c  ....
CSRCS:=$(wildcard ./*.c)

# OBJS 保存所有的中间.o文件的名字列表
OBJS:=$(patsubst %.c, %.o, $(CSRCS))	# 1.o  2.o  3.o  ....

# INC 保存工程中所有的头文件的搜索路径，可以接多个 -I 路径1  -I 路径2 ...
INC:= -I ./ 

# LIBS 保存工程中所有的库的搜索路径 和 指定库的名字，可以接多个, -L 路径1 ... -l 库的名字
LIBS:= -L ./ 


# 生成目标 并 拷贝到tftp服务器的目录下( /home/china/tftp/ )
$(TARGET):$(OBJS)
	$(CC)  $^  $(LIBS)  -o  $@
	cp  $(TARGET)  /home/china/tftp/


# 生成依赖文件
%.o:%.c
	$(CC)  -c  $<  $(INC)  -o  $@


# 清除之前残留的中间文件 main 和 .o文件
# 使用方法 make clean 
clean:
	rm  -rf  $(OBJS)
	rm  -rf  $(TARGET)

