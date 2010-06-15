
CC = mpicc
CFLAG = -O2 -std=c99 -lm

EXEC_FILE = hello_mpi

RM = rm -f

MPIEXEC = mpiexec



all: main.c utils.h
	$(CC) $(CFLAG) main.c -o $(EXEC_FILE)

debug: main.c utils.h
	$(CC) $(CFLAG) -DDEBUG main.c -o $(EXEC_FILE)

exec:
	$(MPIEXEC) -n $(n) ./$(EXEC_FILE)
	mpdallexit
clean:
	$(RM) $(EXEC_FILE)

