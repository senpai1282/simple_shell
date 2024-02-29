CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = shell.c shell_funcs.c string_funcs.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = my_shell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)

.PHONY: all clean
