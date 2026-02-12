SRCS=pipe.c main.c split.c misc.c path.c signal.c


running_executable : $(SRCS)
					gcc -g $(SRCS) -o running_executable

clean:
		rm f -f *.o *.out  running_executable

