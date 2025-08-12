CFLAGS:= -W -pedantic -Wextra -Werror -g -std=gnu89
BINARY:= bin

SOURCES:= $(wildcard *.c)
OBJECTS:= $(SOURCES:.c=.o)
DEPS:= $(OBJECTS:.o=.d)
all: $(BINARY)


$(BINARY): $(OBJECTS)
	@gcc -o  $@ $^

%.o: %.c
	@gcc $(CFLAGS) -MMD -c $^ -o $@

-include $(DEPS)

run: $(BINARY)
	@./$(BINARY)
clean:
	@rm $(OBJECTS) $(BINARY) $(DEPS)

