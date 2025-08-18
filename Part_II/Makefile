BINARY:= bin

SOURCES:= $(wildcard *.c)
OBJECTS:= $(SOURCES:.c=.o)
DEPS:= $(OBJECTS:.o=.d)
LOGFILE:= mpi_errors.log
FILE:= 8597421_scale.txt
N:= 25000000
SPEEDUP:= cores_speedup.txt
all: run

$(BINARY): $(OBJECTS)
	@mpicc -o  $@ $^

%.o: %.c
	@mpicc -MMD -g -c $^ -o $@

-include $(DEPS)

run: $(BINARY)	
	@for i in $$(seq 1 4); do \
		echo "Running Process for $$i Core(s) ....."; \
		mpirun -np $$i ./$(BINARY) $(N) >> $(LOGFILE) 2>&1; \
	done;
	@echo  "SpeedUp" > speedup.txt
	
	@serial=$$(awk 'NR==2 {print $$3}'  $(FILE)); \
	grep $(N) $(FILE) | awk -v s="$$serial" '{print s/ $$3}' >> speedup.txt
	@paste $(FILE) speedup.txt > cores_speedup.txt
	@gnuplot -e "set terminal pngcairo size 1200, 800 font 'Arial, 12'; \
                set title 'Time Vrs Cores'; \
                set grid; \
                set grid back ls 11; \
                set xlabel 'N'; \
                set ylabel 'time(t) sec'; \
                set output 'Time_Performance.png'; \
                plot '$(FILE)' using 2:3 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
		'$(FILE)' using 2:3 title 'Time Performance' smooth csplines with lines lt 7 lc 7 dt 1"
	@gnuplot -e "set terminal pngcairo size 1200, 800 font 'Arial, 12'; \
                set title 'Time Vrs Cores'; \
                set grid; \
                set grid back ls 11; \
                set xlabel 'N'; \
                set ylabel 'time(t) sec'; \
                set output 'Speed_Performance.png'; \
                plot '$(SPEEDUP)' using 2:4 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
                '$(SPEEDUP)' using 2:4 title 'SpeedUP Performance' smooth csplines with lines lt 7 lc 7 dt 1"




clean:
	@rm $(OBJECTS) $(BINARY) $(DEPS) $(LOGFILE) *scale.txt *.png core*.txt s*.txt



