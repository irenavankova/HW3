
EXECUTABLES = omp_bug2 omp_bug3 omp_bug4 omp_bug5 omp_bug6 jacexec gsexec
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

jaco: jacobi-omp.c
	gcc -fopenmp -Wall jacobi-omp.c -lm -o jacexec

run_jaco: jacexec
	./jacexec

gs: gs-omp.c
	gcc -fopenmp -Wall gs-omp.c -lm -o gsexec

run_gs: gsexec
	./gsexec

clean:
	rm -rf $(EXECUTABLES)
