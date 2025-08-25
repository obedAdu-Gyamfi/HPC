
BINARY:= bin
SOURCE:= $(wildcard *.c)
OBJECTS:= $(SOURCE:.c=.o)
DEPS:= $(OBJECTS:.o=.d)

all: run

$(BINARY): $(OBJECTS)
	@mpicc -o $@ $^
%.o: %.c
	@mpicc -MMD -g -c $^ -o $@

-include $(DEPS)

run: $(BINARY)
	@for i in $$(seq 1 2); do \
		mpirun -np $$i ./$(BINARY) 5000 >> error.log 2>&1; \
	done;

clean:
	@rm $(BINARY) $(DEPS) $(OBJECTS) *.log *.txt
