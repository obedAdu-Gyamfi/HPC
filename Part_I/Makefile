SHELL:= /bin/bash
PLOT:= /bin/gnuplot
BINARY:= bin

SOURCES:= $(wildcard *.c)
OBJECTS:= $(SOURCES:.c=.o)
DEPS:= $(OBJECTS:.o=.d)
all: $(BINARY)

#all: 859742_plot.gp

$(BINARY): $(OBJECTS)
	@gcc -o  $@ $^

%.o: %.c
	@gcc  -MMD -g -c $^ -o $@

-include $(DEPS)

#run: $(BINARY)
#	@./$(BINARY)

plot: 8597421_serial.txt
	@gnuplot -e "set terminal pngcairo size 1200, 800 font 'Arial, 12'; \
		set title 'Performance of Serial Program'; \
		set grid; \
		set grid back ls 11; \
		set xlabel 'N'; \
		set ylabel 'time(t) sec'; \
		set output 'Serial_Performance.png'; \
		plot '8597421_serial.txt' using 1:2 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
		'8597421_serial.txt' using 1:2 title 'Vector Vector Multiplication' smooth csplines with lines lt 7 lc 7 dt 1, \
		'8597421_serial.txt' using 1:3 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
		'8597421_serial.txt' using 1:3 title 'Matrix Vector Multiplication' smooth csplines with lines lt 7 lc 9 lw 2 dt 1, \
		'8597421_serial.txt' using 1:4 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
		'8597421_serial.txt' using 1:4 title 'Matrix Matrix Multiplication' smooth csplines with lines lt 7 lc 5 lw 2 dt 1"


run: $(BINARY)
	@./$(BINARY) 5000 && $(MAKE) --no-print-directory plot
clean:
	@rm $(OBJECTS) $(BINARY) $(DEPS) *.txt  *.png



