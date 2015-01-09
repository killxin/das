CC	= gcc
LD	= ld
CFLAGS	= -I./include -O2

CFILES	= $(shell find src/ -name "*.c")
OBJS	= $(CFILES:.c=.o)

weibo: $(OBJS)
	  $(CC)	-o micblog $(OBJS) $(CFLAGS) -lreadline
run:	micblog	testfile/newfriends.txt	testfile/at.txt
	./micblog testfile/newfriends.txt testfile/at.txt 2>&1 | tee log.txt
test1:	micblog	testfile/newfriends1.txt testfile/at1.txt
	./micblog testfile/newfriends1.txt testfile/at1.txt 2>&1 | tee log.txt

submit:
	tar -cvf ./micblog.tar ./
clean:
	-rm -f micblog $(OBJS) $(OBJS:.o=.d) log.txt 2> /dev/null
