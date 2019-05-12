LIBS = lib
OBJS = obj
SRCS = src
SCRP = script

all: include/*.h
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/artigos.c -o $(SRCS)/$(OBJS)/artigos.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/strings.c -o $(SRCS)/$(OBJS)/strings.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/stock.c -o $(SRCS)/$(OBJS)/stock.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/vendas.c -o $(SRCS)/$(OBJS)/vendas.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/read.c -o $(SRCS)/$(OBJS)/read.o
	gcc -Wall -O2 -c $(SRCS)/$(LIBS)/command.c -o $(SRCS)/$(OBJS)/command.o
	gcc -Wall -O2 $(SRCS)/agregador.c -o $(SRCS)/$(OBJS)/*.o -o ag
	gcc -Wall -O2 $(SRCS)/manutencao.c $(SRCS)/$(OBJS)/*.o -o ma
	gcc -Wall -O2 $(SRCS)/servidor.c $(SRCS)/$(OBJS)/*.o -o sv 
	gcc -Wall -O2 $(SRCS)/cliente.c $(SRCS)/$(OBJS)/*.o -o cv
	gcc -Wall -O2 $(SCRP)/script_cv.c -o script_cv
	gcc -Wall -O2 $(SCRP)/script_ma.c -o script_ma

clean:
	rm ma
	rm sv
	rm cv
	rm ag
	rm script_cv
	rm script_ma
	rm $(SRCS)/$(OBJS)/*.o
	rm files/*
