CC = gcc -ansi -pedantic
CFLAGS = -Wall -I ./hdr/
EXE = calculadora
SRC = ./src/
HDR = ./hdr/
OBJ = ./obj/

all : $(EXE) 

.PHONY : clean

clean :
	rm -f $(OBJ)*.o core $(EXE) 

trade_manager.o: $(SRC)trade_manager.c $(HDR)trade_manager.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	mv $@ $(OBJ)

trade.o: $(SRC)trade.c $(HDR)trade.h types.o
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	mv $@ $(OBJ)

types.o: $(SRC)types.c $(HDR)types.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	mv $@ $(OBJ)

calculadora: $(SRC)main.c trade.o trade_manager.o types.o
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $(SRC)main.c $(OBJ)trade.o $(OBJ)trade_manager.o $(OBJ)types.o