SRCS=pipe.c main.c split.c misc.c path.c


running_executanble : $(SRCS)
					gcc -g $(SRCS) -o running_executanble

clean:
		rm f -f *.o *.out  running_executanble

