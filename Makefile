
CC = mpicc
CFLAG = -O2 -std=c99 -lm

EXEC_FILE = hello_mpi

RM = rm -f

MPIEXEC = mpiexec



$(EXEC_FILE): main.c utils.h
	$(CC) $(CFLAG) main.c -o $@

exec:
	$(MPIEXEC) -n $(n) ./$(EXEC_FILE)
clean:
	$(RM) $(EXEC_FILE)

