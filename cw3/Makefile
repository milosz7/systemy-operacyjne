CFLAGS := -pedantic -Wall -std=c99
LFLAGS := $(CFLAGS)
CO     := gcc
LD     := $(CO)

NAMES := $(patsubst %.c,%,$(wildcard *.c))
OBJS := $(patsubst %,%.o,$(NAMES))
EXECS := $(patsubst %,%.x,$(NAMES))

PROCESS_CREATOR_EX := cw3c_process_creator.x

EX_3A_NAME := cw3a
EX_3A_OBJ := $(EX_3A_NAME).o
EX_3A_EXEC := $(EX_3A_NAME).x
EX_3A_DFL_CLI_ARGS := 3 20

EX_3B_NAME := cw3b
EX_3B_OBJ := $(EX_3B_NAME).o
EX_3B_EXEC := $(EX_3B_NAME).x
EX_3B_DEF_CLI_ARGS := $(EX_3A_EXEC) $(EX_3A_DFL_CLI_ARGS)

EX_3C_NAME := cw3c
EX_3C_OBJ := $(EX_3C_NAME).o
EX_3C_EXEC := $(EX_3C_NAME).x
EX_3C_DEF_CLI_ARGS := $(PROCESS_CREATOR_EX) $(EX_3A_EXEC) $(EX_3A_DFL_CLI_ARGS)


.PHONY: help
help:
	@echo "make all - kompiluje wszystkie programy"
	@echo "make print - wypisuje nazwy programów do skompilowania"
	@echo "make <nazwa_pliku> - kompiluje program o podanej nazwie"
	@echo "make run-cw3x - uruchamia program do ćwiczenia 3, podpunkt x, gdzie x od a do c z podstawowymi wybranymi przeze mnie ustawieniami"
	@echo "make clean - usuwa wszystkie pliki stworzone przez make."

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

.PHONY: run-cw3a

run-cw3a: $(EX_3A_EXEC)
	./$(EX_3A_EXEC) $(EX_3A_DFL_CLI_ARGS)

.PHONY: run-cw3b

run-cw3b: $(EX_3B_EXEC) $(EX_3A_EXEC)
	./$(EX_3B_EXEC) $(EX_3B_DEF_CLI_ARGS) 

.phony: run-cw3c

run-cw3c: $(EX_3A_EXEC) $(EX_3C_EXEC) $(PROCESS_CREATOR_EX)
	./$(EX_3C_EXEC) $(EX_3C_DEF_CLI_ARGS)

.PHONY: clean
clean:
	rm *.o *.x