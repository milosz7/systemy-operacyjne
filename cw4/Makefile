CFLAGS := -pedantic -Wall -std=c99
LFLAGS := $(CFLAGS)
CO     := gcc
LD     := $(CO)

NAMES := $(patsubst %.c,%,$(wildcard *.c))
OBJS := $(patsubst %,%.o,$(NAMES))
EXECS := $(patsubst %,%.x,$(NAMES))

EX_EXEC_NAME := cw4
EX_OBJ := $(EX_EXEC_NAME).o
EX_EXEC := $(EX_EXEC_NAME).x
INPUT_FILENAME = cw4in.txt
OUTPUT_FILENAME = cw4out.txt


.PHONY: help
help:
	@echo "make all - kompiluje wszystkie programy"
	@echo "make print - wypisuje nazwy programów do skompilowania"
	@echo "make cw4 - kompiluje program do ćwiczenia 4"
	@echo "make run-cw4 - uruchamia program do ćwiczenia 4"
	@echo "make clean - usuwa wszystkie pliki stworzone przez make"

.PHONY: print
print:
	@echo "Dostępne pliki do skompilowania: $(NAMES)."

.PHONY: all
all: $(OBJS) $(EXECS)

$(OBJS): %.o: %.c
	$(CO) -c $(CFLAGS) $< -o $@

$(EXECS): %.x: %.o 
	$(LD) $(LFLAGS) $< -o $@

.PHONY: $(NAMES)
	
$(NAMES): %: %.x | %.o

.PHONY: run-cw4

run-cw4: $(EX_EXEC)
	./$(EX_EXEC) $(INPUT_FILENAME) $(OUTPUT_FILENAME)
	diff $(INPUT_FILENAME) $(OUTPUT_FILENAME)

.PHONY: clean
clean:
	rm *.o *.x