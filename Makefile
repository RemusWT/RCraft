
CC = clang++
CFlags = -Werror -Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -Wno-error=unused-variable

SRC = $(wildcard src/**/*.cpp)
OBJ = main.o


testing: $(OBJ)
	$(CC) $(OBJ) -o testing

%.o: %.cpp
	$(CC) $(CFlags) -c -o $@ $^

clean:
	rm *.o testing