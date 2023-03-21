CFLAGS := -pedantic -Wall -std=c99
LFLAGS := $(CFLAGS)
CO     := gcc
LD     := $(CO)
RUN_PREFIX = run-

EX_DEP_NAME := print_process
EX_DEP_OBJ := $(EX_DEP_NAME).o
EX_DEP_EXEC := $(EX_DEP_NAME).x

EX_NAME := cw2
EX_OBJ := $(EX_NAME).o
EX_EXEC := $(EX_NAME).x
EX_RUN := $(RUN_PREFIX)$(EX_NAME)

NAMES := $(patsubst %.c,%,$(wildcard *.c))
OBJS := $(patsubst %,%.o,$(NAMES))
EXECS := $(patsubst %,%.x,$(NAMES))

.PHONY: help
help:
	@echo "make all - kompiluje wszystkie programy"
	@echo "make cw2 - kompiluje program do ćwiczenia 2"
	@echo "make run-cw2 - uruchamia program do ćwiczenia 2"
	@echo "make clean - usuwa wszystkie pliki stworzone przez make."

.PHONY: all
all: $(OBJS) $(EXECS)
	@echo "$(EXERCISE_NAMES)"

$(OBJS): %.o: %.c
	$(CO) -c $(CFLAGS) $< -o $@

$(EXECS): %.x: %.o 
	$(LD) $(LFLAGS) $< -o $@

.PHONY: $(EX_NAME)
$(EX_NAME): %: %.x | $(EX_DEP_OBJ) $(EX_DEP_EXEC) %.o 

.PHONY: $(EX_RUN)
$(EX_RUN):
	./$(EX_EXEC) $(EX_DEP_EXEC)

.PHONY: clean
clean:
	rm *.o *.x