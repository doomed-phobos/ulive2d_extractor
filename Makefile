CC=gcc
CFLAGS=-std=c2x -Wall
PROJECT_NAME=sp_hack
Live2D_DIR=./third_party/Live2DCubismCore
Live2D_INCLUDE_DIR=${Live2D_DIR}/include
Live2D_STATIC_LIBRARY=${Live2D_DIR}/lib/linux/x86_64/libLive2DCubismCore.a

build: main.c live2d.c file.c
	${CC} ${CFLAGS} -I${Live2D_INCLUDE_DIR} -o ${PROJECT_NAME} $^ ${Live2D_STATIC_LIBRARY} -lm

clean:
	rm ${PROJECT_NAME} *.o