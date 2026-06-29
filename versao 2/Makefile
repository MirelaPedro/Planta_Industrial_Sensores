CC = gcc
RM = rm
TARGET = planta

all: objetos
	$(CC) main.o -o $(TARGET)

objetos: main.c 
	$(CC) -c main.c

clean:
	$(RM) *.o 
	$(RM) $(TARGET)		
