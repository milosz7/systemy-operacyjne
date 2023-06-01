LFLAGS 	:= -Wall -std=c99 -pedantic -fPIC
CFLAGS 	:= $(LFLAGS)
CO     	:= gcc
LD     	:= $(CO)
AR     	:= ar
ARFLAGS := rsv

NAMES := $(patsubst %.c,%,$(wildcard *.c))

# EXECS_S := $(patsubst %,%s.x,$(NAMES))
# EXECS_D1 := $(patsubst %,%d1.x,$(NAMES))
# EXECS_D2 := $(patsubst %,%d2.x,$(NAMES))

EX_NAME := cw9
EX_OBJ := $(EX_NAME).o
EX_EXEC_S := $(EX_NAME)s.x
EX_EXEC_D1 := $(EX_NAME)d1.x
EX_EXEC_D2 := $(EX_NAME)d2.x

LIB_OBJ := source/utils.o

LIB_DIR := ./lib
LIB_NAME := utils
LIB_STAT := lib$(LIB_NAME).a
LIB_SHAR := lib$(LIB_NAME).so
LD_LIBS := -lpthread

EXAMPLE_SECTIONS_AMT := 3
EXAMPLE_THREADS_AMT := 3



DYNAMIC_LIB_EXPORT_PATH := export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH};

.PHONY: print
print:
	@echo "\n\"make cw9s / cw9d1 / cw9d2\" - - kompiluje program do ćwiczenia 8 kolejno używając biblioteki statycznej / dzielonej / dzielonej dołączanej na drugi sposób"
	@echo "\n\"make run-cw9s / cw9d1 / cw9d2\" - kompiluje i uruchamia program do ćwiczenia 8 kolejno używając biblioteki statycznej / dzielonej / dzielonej dołączanej na drugi sposób"
	@echo "\n\"make all\" - kompiluje program i biblioteki na wszystkie możliwe powyżej sposoby jednocześnie"

$(LIB_STAT): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(LIB_SHAR): $(LIB_OBJ)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJ)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

$(EX_EXEC_S): $(EX_OBJ) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS)

$(EX_EXEC_D1): $(EX_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS) -Wl,-R $(LIB_DIR)

$(EX_EXEC_D2): $(EX_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS)


.PHONY: cw9s run-cw9s

cw9s: $(EX_EXEC_S)

run-cw9s: $(EX_EXEC_S)
	clear
	./$(EX_EXEC_S) $(EXAMPLE_THREADS_AMT) $(EXAMPLE_SECTIONS_AMT)
	
.PHONY: cw9d1 run-cw9d1

cw9d1: $(EX_EXEC_D1)

run-cw9d1: $(EX_EXEC_D1)
	clear
	./$(EX_EXEC_D1) $(EXAMPLE_THREADS_AMT) $(EXAMPLE_SECTIONS_AMT)

.PHONY: cw9d2 run-cw9d2

cw8d2: $(EXECS_D1)

run-cw8d2: $(EXECS_D2)
	$(DYNAMIC_LIB_EXPORT_PATH) \
	./$(EX_EXEC_D2) $(EXAMPLE_THREADS_AMT) $(EXAMPLE_SECTIONS_AMT)

.PHONY: all
all: $(EX_EXEC_S) $(EX_EXEC_D1) $(EX_EXEC_D2) 

clean:
	rm  *.[ox] ./**/*.[ox]
	rm -rf ./$(LIB_DIR)
