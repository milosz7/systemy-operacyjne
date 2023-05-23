LFLAGS 	:= -Wall -std=gnu99 -pedantic -fPIC
CFLAGS 	:= $(LFLAGS)
CO     	:= gcc
LD     	:= $(CO)
AR     	:= ar
ARFLAGS := rsv

NAMES := $(patsubst %.c,%,$(wildcard *.c))

EXECS_S := $(patsubst %,%s.x,$(NAMES))
EXECS_D1 := $(patsubst %,%d1.x,$(NAMES))
EXECS_D2 := $(patsubst %,%d2.x,$(NAMES))

LIB_OBJS_SEM := source/semaphores.o

LIB_OBJS_SHM :=  source/sharedmemory.o

LIB_DIR := ./lib
LIB_NAME := cw7utils
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so
LDLIBS := 

INPUT_FILENAME := input.txt
OUTPUT_FILENAME := output.txt

EX_NAME := cw7
EX_PRODUCER_NAME := producer
EX_CONSUMER_NAME := consumer

EX_NAME_OBJ := $(EX_NAME).o
EX_PRODUCER_NAME_OBJ := $(EX_PRODUCER_NAME).o
EX_CONSUMER_NAME_OBJ := $(EX_CONSUMER_NAME).o

EX_CONSUMER_NAME_EXEC_S := $(EX_CONSUMER_NAME)s.x
EX_PRODUCER_NAME_EXEC_S := $(EX_PRODUCER_NAME)s.x

EX_CONSUMER_NAME_EXEC_D1 := $(EX_CONSUMER_NAME)d1.x
EX_PRODUCER_NAME_EXEC_D1 := $(EX_PRODUCER_NAME)d1.x

EX_CONSUMER_NAME_EXEC_D2 := $(EX_CONSUMER_NAME)d2.x
EX_PRODUCER_NAME_EXEC_D2 := $(EX_PRODUCER_NAME)d2.x

EX_NAME_EXEC_S := $(EX_NAME)s.x
EX_NAME_EXEC_D1 := $(EX_NAME)d1.x
EX_NAME_EXEC_D2 := $(EX_NAME)d2.x

.PHONY: print
print:
	@echo "\n\"make cw7s / cw7d1 / dw7d2\" - kompiluje program do ćwiczenia 7 kolejno używając biblioteki statycznej / dzielonej / dzielonej dołączanej na drugi sposób"
	@echo "\n\"make run-cw7s / cw7d1 / cw7d2\" - kompiluje i uruchamia program do ćwiczenia 7 kolejno używając biblioteki statycznej / dzielonej / dzielonej dołączanej na drugi sposób"
	@echo "\n\"make all\" - kompiluje program i biblioteki na wszystkie możliwe powyżej sposoby jednocześnie"

$(LIB_STAT): $(LIB_OBJS_SEM) $(LIB_OBJS_SHM)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(LIB_SHAR): $(LIB_OBJS_SHM) $(LIB_OBJS_SEM)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS_SHM) $(LIB_OBJS_SEM)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

$(EX_CONSUMER_NAME_EXEC_S) : $(EX_CONSUMER_NAME_OBJ) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME)

$(EX_PRODUCER_NAME_EXEC_S) : $(EX_PRODUCER_NAME_OBJ) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME)

$(EX_NAME_EXEC_S): $(EX_NAME_OBJ) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME)

$(EX_CONSUMER_NAME_EXEC_D2): $(EX_CONSUMER_NAME_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EX_PRODUCER_NAME_EXEC_D2): $(EX_PRODUCER_NAME_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EX_NAME_EXEC_D2): $(EX_NAME_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EX_CONSUMER_NAME_EXEC_D1): $(EX_CONSUMER_NAME_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EX_PRODUCER_NAME_EXEC_D1): $(EX_PRODUCER_NAME_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EX_NAME_EXEC_D1): $(EX_NAME_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

.PHONY: cw7s run-cw7s
cw7s: $(EXECS_S)

run-cw7s: $(EXECS_S)
	./$(EX_NAME_EXEC_S) $(EX_CONSUMER_NAME_EXEC_S) $(EX_PRODUCER_NAME_EXEC_S) $(INPUT_FILENAME) $(OUTPUT_FILENAME)
	@echo " "
	diff $(INPUT_FILENAME) $(OUTPUT_FILENAME)

.PHONY: cw7d1 run-cw7d1
cw7d1: $(EXECS_D1)

.PHONY: cw7d2 run-cw7d2
cw7d2: $(EXECS_D2)

run-cw7d1: $(EXECS_D1)
	./$(EX_NAME_EXEC_D1) $(EX_CONSUMER_NAME_EXEC_D1) $(EX_PRODUCER_NAME_EXEC_D1) $(INPUT_FILENAME) $(OUTPUT_FILENAME)
	@echo " "
	diff $(INPUT_FILENAME) $(OUTPUT_FILENAME)

run-cw7d2: $(EXECS_D2)
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EX_NAME_EXEC_D2) $(EX_CONSUMER_NAME_EXEC_D2) $(EX_PRODUCER_NAME_EXEC_D2) $(INPUT_FILENAME) $(OUTPUT_FILENAME)
	@echo " "
	diff $(INPUT_FILENAME) $(OUTPUT_FILENAME)

.PHONY: all
all: $(EXECS_S) $(EXECS_D1) $(EXECS_D2)

clean:
	rm  *.[ox] ./**/*.[ox]
	rm -rf ./$(LIB_DIR)
