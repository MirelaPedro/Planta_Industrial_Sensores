CC = gcc
RM = rm // para windows use del; para linux use rm
TARGET = planta
SRC = ./src
OBJS = ./objs

all: objetos
	$(CC) $(OBJS)/main.o $(OBJS)/creates.o $(OBJS)/deletes.o $(OBJS)/formatting.o $(OBJS)/menus.o $(OBJS)/reads.o $(OBJS)/searchs.o $(OBJS)/updates.o $(OBJS)/verifications.o -o $(TARGET)

objetos: main.c 
	$(CC) -c main.c -o $(OBJS)/main.o
	$(CC) -c $(SRC)/menus.c -o $(OBJS)/menus.o
	$(CC) -c $(SRC)/creates.c -o $(OBJS)/creates.o
	$(CC) -c $(SRC)/reads.c -o $(OBJS)/reads.o
	$(CC) -c $(SRC)/searchs.c -o $(OBJS)/searchs.o
	$(CC) -c $(SRC)/updates.c -o $(OBJS)/updates.o
	$(CC) -c $(SRC)/verifications.c -o $(OBJS)/verifications.o

clean:
	$(RM) $(OBJS)/*.o 
	$(RM) $(TARGET)		
