LIBS = lib
OBJS = obj
SRCS = src

all: include/*.h
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/artigos.c -o $(SRCS)/$(OBJS)/artigos.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/strings.c -o $(SRCS)/$(OBJS)/strings.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/stock.c -o $(SRCS)/$(OBJS)/stock.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/read.c -o $(SRCS)/$(OBJS)/read.o
	gcc -Wall -O2 $(SRCS)/manutencao.c $(SRCS)/$(OBJS)/*.o -o ma
	gcc -Wall -O2 $(SRCS)/servidor.c $(SRCS)/$(OBJS)/*.o -o sv 
	gcc -Wall -O2 $(SRCS)/cliente.c $(SRCS)/$(OBJS)/*.o -o cv
	gcc -Wall -O2 $(SRCS)/agregador.c $(SRCS)/$(OBJS)/*.o -o ag

clean:
	rm ma
	rm sv
	rm cv
	rm ag
	rm $(SRCS)/$(OBJS)/*.o
	rm files/*
