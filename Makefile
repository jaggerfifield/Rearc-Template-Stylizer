LINK := -lSDL2

ifeq ($(OS), Windows_NT)
	DEF = -D$(OS)
endif

TARGET := rearc
DEP := main.o canvas.o line.o keys.o menu.o
FLAGS := -Wall -c -g

all: $(DEP)
	@echo ===== Comiple main.c =====
	gcc -ggdb -o $(TARGET) $(DEF) $(LINK) $(DEP)

main.o : main.c
	@echo ===== Compile main.c =====
	gcc $(LINK) $(FLAGS) main.c
	@echo

canvas.o: canvas.c
	@echo ===== Compile canvas.c =====
	gcc $(LINK) $(FLAGS) canvas.c
	@echo

line.o: line.c
	@echo ===== Compile line.c =====
	gcc $(LINK) $(FLAGS) line.c
	@echo

keys.o: keys.c
	@echo ===== Compile keys.c =====
	gcc $(LINK) $(FLAGS) keys.c
	@echo

menu.o: menu.c
	@echo ===== Compile menu.c =====
	gcc $(LINK) $(FLAGS) menu.c
	@echo

clean:
	@echo ===== Clean =====
	rm -r ./*.o
	rm -r ./$(TARGET)
