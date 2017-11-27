# makefile for mpi runs
# 2 November 2017
CC = mpic++
CFLAGS = -g
#PROGRAM = test3
PROGRAM = solution
N_CORES = 1
all:
	$(CC) $(CFLAS) $(PROGRAM).cpp -o $(PROGRAM)
	mpirun -np $(N_CORES) ./$(PROGRAM)
make clean:
	rm -rf $(PROGRAM)
        
