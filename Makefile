
EXECUTABLES = omp_bug2 omp_bug3 omp_bug4 omp_bug5 omp_bug6 
COMPILER = gcc
FLAGS = -fopenmp

all: $(EXECUTABLES)


omp_bug2: omp_bug2.c
	gcc -fopenmp omp_bug2.c -o omp_bug2

bug2: omp_bug2
	./omp_bug2

omp_bug3: omp_bug3.c
	gcc -fopenmp omp_bug3.c -o omp_bug3

bug3: omp_bug3
	./omp_bug3

omp_bug4: omp_bug4.c
	gcc -fopenmp omp_bug4.c -o omp_bug4

bug4: omp_bug4
	./omp_bug4

omp_bug5: omp_bug5.c
	gcc -fopenmp omp_bug5.c -o omp_bug5

bug5: omp_bug5
	./omp_bug5

omp_bug6: omp_bug6.c
	gcc -fopenmp omp_bug6.c -o omp_bug6

bug6: omp_bug6
	./omp_bug6

ssort: ssort.c
	$(COMPILER) $(FLAGS) ssort.c -o ssort

sort_all: ssort
	mpirun -np 4 ./ssort

clean:
	rm -rf $(EXECUTABLES)
