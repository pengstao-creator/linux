all:nonSem nameSem

nonSem:nonSem.c
	@gcc -o $@ $^ -lpthread
nameSem:nameSem.c
	@gcc -o $@ $^ -lpthread
.PHONY:clean
clean:
	@rm -rf nameSem