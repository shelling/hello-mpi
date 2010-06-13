
CC = mpicc
FLAG = -O2 -std=c99
MPIEXEC = mpiexec
RM = rm -f

EXEC_FILE = mpi_hello


$(EXEC_FILE): main.c
	$(CC) $(FLAG) $< -o $@

exec:
	$(MPIEXEC) -n $(PROCS) ./$(EXEC_FILE)
clean:
	$(RM) $(EXEC_FILE)

