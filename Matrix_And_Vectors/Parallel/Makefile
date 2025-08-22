BINARY:= bin

SOURCES:= $(wildcard *.c)
OBJECTS:= $(SOURCES:.c=.o)
DEPS:= $(OBJECTS:.o=.d)
LOGFILE:= mpi_errors.log
FILE:= 8597421_scale.txt
N:= 250000000
SPEEDUP:= cores_speedup.txt
EFFIC:= efficiency.txt
PERFORM:= performance_analysis.txt
HOST=host.txt
all: run

$(BINARY): $(OBJECTS)
	@mpicc -o  $@ $^

%.o: %.c
	@mpicc -MMD -g -c $^ -o $@

-include $(DEPS)

run: $(BINARY)	
	@for i in $$(seq 1 8); do \
		echo "Running Process with $$i Core(s) ....."; \
		mpirun -np $$i -hostfile $(HOST) ./$(BINARY) $(N) >> $(LOGFILE) 2>&1; \
	done;
	@echo  "SpeedUp" > speedup.txt
	@echo "Efficiency" > $(EFFIC)
	@serial=$$(awk 'NR==2 {print $$3}'  $(FILE)); \
	grep $(N) $(FILE) | awk -v s="$$serial" '{print s / $$3}' >> speedup.txt; \
	grep $(N) $(FILE) | awk -v b="$$serial" '{print b / ($$2 * $$3)}' >> $(EFFIC)
	@paste $(FILE) speedup.txt > cores_speedup.txt
	@paste cores_speedup.txt $(EFFIC) > performance_analysis.txt
	@gnuplot -e "set terminal pngcairo size 1200, 800 font 'Arial, 12'; \
                set title 'Time Vrs Cores'; \
                set grid; \
                set grid back ls 11; \
                set xlabel 'N'; \
                set ylabel 'time(t) sec'; \
                set output 'Time_Performance.png'; \
		set key top left; \
                plot '$(PERFORM)' using 2:3 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
		'$(PERFORM)' using 2:3 title 'Time Performance' smooth csplines with lines lt 7 lc 7 dt 1"
	@gnuplot -e "set terminal pngcairo size 1200, 800 font 'Arial, 12'; \
                set title 'Time Vrs Cores'; \
                set grid; \
                set grid back ls 11; \
                set xlabel 'N'; \
                set ylabel 'time(t) sec'; \
                set output 'Speed_Performance.png'; \
		set key top left; \
                plot '$(PERFORM)' using 2:4 title '.'  with points lt 7 lc 2 lw 2 dt 1, \
                '$(PERFOM)' using 2:4 title 'SpeedUP Performance' smooth csplines with lines lt 7 lc 7 dt 1, \
		'$(PERFORM)' using 2:5 title 'Efficiecy' with lines dashtype 7 lc 8"

clean:
	@rm *.png 8*.txt $(OBJECTS) $(BINARY) $(DEPS) $(LOGFILE) $(PERFORM) $(SPEEDUP) $(EFFIC) s*.txt

