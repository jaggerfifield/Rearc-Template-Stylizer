LINK := -lSDL2

ifeq ($(OS), Windows_NT)
	LINK := -lmingw32 -lSDL2main -lSDL2
	IPATH := -I.\SDL2\include
	LPATH := -L.\SDL2\lib
endif

TARGET := rearc
DEP := main.o canvas.o line.o keys.o menu.o
FLAGS := -Wall -c -g
GROUP := $(IPATH) $(FLAGS)

all: $(DEP)
	@echo ===== Comiple all =====
	gcc -ggdb -o $(TARGET) $(DEP) $(LPATH) $(LINK)

main.o : main.c
	@echo ===== Compile main.c =====
	gcc $(GROUP) main.c
	@echo

canvas.o: canvas.c
	@echo ===== Compile canvas.c =====
	gcc $(GROUP) canvas.c
	@echo

line.o: line.c
	@echo ===== Compile line.c =====
	gcc $(GROUP) line.c
	@echo

keys.o: keys.c
	@echo ===== Compile keys.c =====
	gcc $(GROUP) keys.c
	@echo

menu.o: menu.c
	@echo ===== Compile menu.c =====
	gcc $(GROUP) menu.c
	@echo

clean:
	@echo ===== Clean =====
	rm -r ./*.o
	rm -r ./$(TARGET)
