
CC          = g++
LD          = g++ 
CFLAG       = -lpapi -lm -std=c++11 
PROG_NAME   = synthetic

SRC_DIR     = ./source
BUILD_DIR   = ./build
BIN_DIR     = ./bin
SRC_LIST = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST = $(BUILD_DIR)/$(notdir $(SRC_LIST:.cpp=.o))

.PHONY: all clean $(PROG_NAME) compile

all: $(PROG_NAME)

compile:
	$(CC) -c $(CFLAG) $(CFLAGS) $(SRC_LIST) -o $(OBJ_LIST)

$(PROG_NAME): compile
	$(LD) $(OBJ_LIST) -o $(BIN_DIR)/$@ $(CFLAG)

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*.o
