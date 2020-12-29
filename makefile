CC = gcc -ansi -pedantic
CFLAGS = -Wall -I ./hdr/
EXE = trading
SRC = ./src/
HDR = ./hdr/
OBJ = ./obj
TST = ./tests
OBJECTS = trade_manager.o trade.o types.o date.o list.o
TESTS = list_test
DIRECTORIES = obj tests log

all : $(DIRECTORIES) $(EXE) $(TESTS) 

.PHONY : clean

clean :
	rm -f core $(EXE) 
	rm -r $(TST) $(OBJ)

obj:
	mkdir $@

tests:
	mkdir $@

log:
	mkdir $@

trade_manager.o: $(SRC)trade_manager.c $(HDR)trade_manager.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	mv $@ $(OBJ)

trade.o: $(SRC)trade.c types.o date.o
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

date.o: $(SRC)date.c $(HDR)date.h types.o 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	mv $@ $(OBJ)

list.o: $(SRC)list.c $(HDR)list.h types.o trade.o
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
	mv $@ $(OBJ)


trading: $(SRC)main.c trade.o trade_manager.o types.o list.o date.o
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $(SRC)main.c $(OBJ)/trade.o $(OBJ)/trade_manager.o $(OBJ)/types.o $(OBJ)/list.o $(OBJ)/date.o

list_test: $(SRC)list_test.c trade.o list.o types.o date.o
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $(SRC)list_test.c $(OBJ)/trade.o $(OBJ)/trade_manager.o $(OBJ)/types.o $(OBJ)/list.o $(OBJ)/date.o
	mv $@ $(TST)