
CC = clang++
CFlags = -Werror -Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -Wno-error=unused-variable

SRC = $(wildcard src/**/*.cpp)
OBJ = $(SRC:.c=.o)

BINARY = RCraft


$(BINARY): $(OBJ)
	$(CC) $(OBJ) -o bin/x64/$(BINARY)

%.o: %.cpp
	$(CC) $(CFlags) -c -o $@ $^

clean:
	rm *.o testing