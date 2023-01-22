
CC = clang++
# -Wconversion 
# -Xinerama
CFlags = -Werror -Wall -Wextra  -Wunreachable-code -Wuninitialized -Wno-error=unused-variable -Wno-error=unused-parameter -Wno-error=unused-comparison
IFLAGS = -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sysprof-4 -pthread
LFlags = -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXcursor -lfreetype

SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

BINARY = RCraft

all: dirs game

game: $(OBJ_DIR)$(OBJ)
	$(CC) $^ -o bin/x64/$(BINARY)  $(LFlags)

%.o: %.cpp
	$(CC) $(CFlags) $(IFLAGS) -c -o $@ $^

dirs:
	mkdir -p bin/x64/


clean:
	rm *.o testing