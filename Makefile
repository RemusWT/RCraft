
CC = clang++
# -Wconversion 
CFlags = -Werror -Wall -Wextra  -Wunreachable-code -Wuninitialized -Wno-error=unused-variable -Wno-error=unused-parameter
LFlags = -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -Xinerama -lXcursor

SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

BINARY = RCraft

all: dirs game

game: $(OBJ_DIR)$(OBJ)
	$(CC) $^ -o bin/x64/$(BINARY) $(LFlags)

%.o: %.cpp
	$(CC) $(CFlags) -c -o $@ $^

dirs:
	mkdir -p bin/x64/


clean:
	rm *.o testing