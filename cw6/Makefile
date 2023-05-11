CFLAGS 	:= -pedantic -Wall -std=c99
LFLAGS 	:= $(CFLAGS)
CO     	:= gcc
LD     	:= $(CO)
AR     	:= ar
ARFLAGS := rsv

LIB_NAMES := $(patsubst %.c,%,$(wildcard source/*.c))
LIB_SOURCE := $(patsubst %,%.c,$(LIB_NAMES))
LIB_OBJS := $(patsubst %,%.o,$(LIB_NAMES))
EXECS := $(patsubst %,%.x,$(NAMES))

NAMES := $(patsubst %.c,%,$(wildcard *.c))
OBJS := $(patsubst %,%.o,$(NAMES))
EXECS := $(patsubst %,%.x,$(NAMES))

LIB_DIR := ./lib
LIB_NAME := semaphores
LIB_STAT = lib$(LIB_NAME).a
LDLIBS := -lm

EX_NAME := cw6
EX_EXEC := $(EX_NAME).x
EX_PROCESS_CREATOR_NAME := process_creator
EX_PROCESS_CREATOR_EXEC := $(EX_PROCESS_CREATOR_NAME).x
EX_COUNTER_FILENAME := counter.txt
EX_SECTIONS_NUMBER := 2
EX_PROCESSES_NUMBER := 2

$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(OBJS): %.o: %.c $(LIB_STAT)
	$(CO) -c $(CFLAGS) $< -o $@

$(EXECS): %.x: %.o $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

.PHONY: all
all: $(OBJS) $(EXECS)

.PHONY: run-cw6

run-cw6: $(EX_EXEC) $(EX_PROCESS_CREATOR_EXEC) $(LIB_STAT)
	./$(EX_EXEC) $(EX_PROCESS_CREATOR_EXEC) $(EX_PROCESSES_NUMBER) $(EX_SECTIONS_NUMBER) $(EX_COUNTER_FILENAME)

clean:
	rm  *.[oax] ./**/*.[oax]
