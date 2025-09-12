SHELL:= /bin/bash
PLOT:= /bin/gnuplot
BINARY:= bin

SOURCES:= $(wildcard *.c)
OBJECTS:= $(SOURCES:.c=.o)
DEPS:= $(OBJECTS:.o=.d)
N:= 100
all: run

$(BINARY): $(OBJECTS)
	@gcc -o  $@ $^

%.o: %.c
	@gcc  -MMD -g -c $^ -o $@

-include $(DEPS)

run: $(BINARY)
	@echo "Beginning process ..."
	@./$(BINARY) $(N)
	@echo "Beginning Plot ..."	
	@gnuplot -e "set terminal pngcairo size 1200, 800 font 'Arial, 12'; \
                set title 'Performance of Serial Program'; \
                set grid; \
                set grid back ls 11; \
                set xlabel 'N'; \
                set ylabel 'time(t) sec'; \
                set output 'Serial_Performance.png'; \
		set key top left; \
                plot '8597421_serial.txt' using 1:2 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
                '8597421_serial.txt' using 1:2 title 'Vector Vector Multiplication' smooth csplines with lines lt 7 lc 7 dt 1, \
                '8597421_serial.txt' using 1:3 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
                '8597421_serial.txt' using 1:3 title 'Matrix Vector Multiplication' smooth csplines with lines lt 7 lc 9 lw 2 dt 1, \
                '8597421_serial.txt' using 1:4 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
                '8597421_serial.txt' using 1:4 title 'Matrix Matrix Multiplication' smooth csplines with lines lt 7 lc 5 lw 2 dt 1"
	@echo "Job Done!"
clean:
	@rm $(OBJECTS) $(BINARY) $(DEPS) *.txt  *.png



