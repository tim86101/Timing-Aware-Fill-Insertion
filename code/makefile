DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC}))

TARGET = CAD

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -Wall -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {}

test:
	./bin/CAD ./input/test/circuit1.conf
circuit1:
	./bin/CAD ./input/circuit1/circuit1.conf
circuit2:
	./bin/CAD ./input/circuit2/circuit2.conf
circuit3:
	./bin/CAD ./input/circuit3/circuit3.conf
circuit4:
	./bin/CAD ./input/circuit4/circuit4.conf
circuit5:
	./bin/CAD ./input/circuit5/circuit5.conf

checktest:
	./bin/layoutchecker ./input/test/circuit1.cut ./output/test.fill ./input/test/rule.dat 20 
checkcircuit1:
	./bin/layoutchecker ./input/circuit1/circuit1.conf
checkcircuit2:
	./bin/layoutchecker ./input/circuit2/circuit2.conf
checkcircuit3:
	./bin/layoutchecker ./input/circuit3/circuit3.conf
checkcircuit4:
	./bin/layoutchecker ./input/circuit4/circuit4.conf
checkcircuit5:
	./bin/layoutchecker ./input/circuit5/circuit5.conf
