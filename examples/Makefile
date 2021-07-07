.PHONY : dummy

CC	= gcc -g
CXX	= g++ -g 
MAKE= $(CC)
CFLAGS	= -I ..
LDFLAGS	= 
ALL_FILE= main

%.i : %.c
	$(MAKE) -E -o $@ $< $(CFLAGS)

%.i : %.cpp
	$(MAKE) -E -o $@ $< $(CFLAGS)

%.o : %.c
	$(MAKE) -c -o $@ $< $(CFLAGS)

%.o : %.cpp
	$(MAKE) -c -o $@ $< $(CFLAGS)

all : $(ALL_FILE)

clean : dummy
	rm -rf *.o *.i $(ALL_FILE)

main: main.o ../easylog.o
	$(MAKE) -o $@ $^ $(CFLAGS) $(LDFLAGS)

