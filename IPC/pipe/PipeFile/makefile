PATH_NAME = ./pipe.fifo
all:processA processB
processA:processA.c pipeFile.h
	@gcc -o $@ $^
processB:processB.c pipeFile.h
	@gcc -o $@ $^
.PHONY:clean
clean:
	@rm -f processA processB
	@rm -f $(PATH_NAME)