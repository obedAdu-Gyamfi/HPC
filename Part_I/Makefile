SHELL:= /bin/bash
PLOT:= /bin/gnuplot
BINARY:= bin

SOURCES:= $(wildcard *.c)
OBJECTS:= $(SOURCES:.c=.o)
DEPS:= $(OBJECTS:.o=.d)
all: $(BINARY)


$(BINARY): $(OBJECTS)
	@gcc -o  $@ $^

%.o: %.c
	@gcc  -MMD -g -c $^ -o $@

-include $(DEPS)

run: $(BINARY)
	@./$(BINARY) 
clean:
	@rm $(OBJECTS) $(BINARY) $(DEPS)

script:
	@echo "starting script..."



