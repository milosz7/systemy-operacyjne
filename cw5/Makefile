CFLAGS := -pedantic -Wall -std=c99
LFLAGS := $(CFLAGS)
CO     := gcc
LD     := $(CO)

NAMES := $(patsubst %.c,%,$(wildcard *.c))
OBJS := $(patsubst %,%.o,$(NAMES))
EXECS := $(patsubst %,%.x,$(NAMES))

EX_EXEC_NAME_5A := cw5a
EX_OBJ_5A := $(EX_EXEC_NAME_5A).o
EX_EXEC_5A := $(EX_EXEC_NAME_5A).x
EX_5_READ_NAME := cw5a_read
EX_5_READ_OBJ := $(EX_5_READ_NAME).o
EX_5_READ_EXEC := $(EX_5_READ_NAME).x
EX_5_WRITE_NAME := cw5a_write
EX_5_WRITE_OBJ := $(EX_5_WRITE_NAME).o
EX_5_WRITE_EXEC := $(EX_5_WRITE_NAME).x
INPUT_FILENAME = cw5in.txt
OUTPUT_FILENAME = cw5out.txt
FIFO_PATH := ./pipe.FIFO


.PHONY: help
help:
	@echo "make all - kompiluje wszystkie programy"
	@echo "make print - wypisuje nazwy programów do skompilowania"
	@echo "make cw5x - kompiluje program do ćwiczenia 5x , gdzie x to a lub b"
	@echo "make run-cw5x - uruchamia program do ćwiczenia 5x, gdzie x to a lub b"
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

.PHONY: run-cw5a

run-cw5a: $(EXECS)
	./$(EX_EXEC_5A) $(INPUT_FILENAME) $(OUTPUT_FILENAME) $(FIFO_PATH)
	diff $(INPUT_FILENAME) $(OUTPUT_FILENAME)

.PHONY: run-cw5b

.PHONY: run-cw5b-read

run-cw5b-read: $(EX_5_READ_OBJ) $(EX_5_READ_EXEC)
	./$(EX_5_READ_EXEC) $(INPUT_FILENAME) $(FIFO_PATH)

.PHONY: run-cw5b-write

run-cw5b-write: $(EX_5_WRITE_OBJ) $(EX_5_WRITE_EXEC)
	./$(EX_5_WRITE_EXEC) $(OUTPUT_FILENAME) $(FIFO_PATH)

run-cw5b: 
	@mknod $(FIFO_PATH) p
	$(MAKE) -j2 run-cw5b-read run-cw5b-write
	diff $(INPUT_FILENAME) $(OUTPUT_FILENAME)
	@rm $(FIFO_PATH)
	

.PHONY: clean
clean:
	rm *.o *.x