MONGOOSE_INC=/home/ubuntu/Embedded/linux/AdvertisingPlayer/3rd-lib/include
MONGOOSE_SRC=/home/ubuntu/Embedded/linux/AdvertisingPlayer/3rd-lib/src/mongoose.c

mongoosetest: momgoosetest.c $(MONGOOSE_SRC)
	@gcc -o $@ $^ -I $(MONGOOSE_INC) -lpthread
.PHONY:clean
clean:
	@rm -rf mongoosetest
