# OpenMP_Benchmarks

#### Parallel programming benchmarking using OpenMP methods.

Comparison of efficiency improvement between a linear version and a parallel version of the same code.

Execution timing and results commenting.



## primes.c  (Prime numbers parallelization)

How to run:

Step 1 -> 

	gcc primes.c -fopenmp

Step 2 -> 
	
 	./a.out

## gaussian.c (Applying gaussian blur to a given image)

How to run:

Step 1 ->  
            
	gcc gaussian.c -fopenmp -lm

Step 2 ->       

	./a.out <blur-radius> <filename>, 

e.g. ./a.out  2  500.bmp


## task_dependencies.c (Task dependencies and synchronization problems)

How to run:

Step 1 -> openMP_execution_model.txt needs to be in the same scope as the task_dependencies.c file

Step 2 -> 

 	gcc task_dependencies.c

Step 3 ->

 	./a.out

  

 	
