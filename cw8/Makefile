LFLAGS 	:= -Wall -std=c99 -pedantic -fPIC
CFLAGS 	:= $(LFLAGS)
CO     	:= gcc
LD     	:= $(CO)
AR     	:= ar
ARFLAGS := rsv

NAMES := $(patsubst %.c,%,$(wildcard *.c))

EXECS_S := $(patsubst %,%s.x,$(NAMES))
EXECS_D1 := $(patsubst %,%d1.x,$(NAMES))
EXECS_D2 := $(patsubst %,%d2.x,$(NAMES))

LIB_OBJS_MQ := source/mqutils.o

LIB_DIR := ./lib
LIB_NAME := mqutils
LIB_STAT := lib$(LIB_NAME).a
LIB_SHAR := lib$(LIB_NAME).so
LD_LIBS := -lrt -lm

SERVER_NAME := server
CLIENT_NAME := client

SERVER_OBJ := $(SERVER_NAME).o
CLIENT_OBJ := $(CLIENT_NAME).o

SERVER_EXEC_S := $(SERVER_NAME)s.x
CLIENT_EXEC_S := $(CLIENT_NAME)s.x

SERVER_EXEC_D1 := $(SERVER_NAME)d1.x
CLIENT_EXEC_D1 := $(CLIENT_NAME)d1.x

SERVER_EXEC_D2 := $(SERVER_NAME)d2.x
CLIENT_EXEC_D2 := $(CLIENT_NAME)d2.x

RUN_SERVER := xterm -title $(SERVER_NAME) -bg red -fg white -e
RUN_CLIENT := xterm -title $(CLIENT_NAME) -bg green -fg black -e

DYNAMIC_LIB_EXPORT_PATH := export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH};

.PHONY: print
print:
	@echo "\n\"make cw8s / cw8d1 / cw8d2\" - - kompiluje program do ćwiczenia 8 kolejno używając biblioteki statycznej / dzielonej / dzielonej dołączanej na drugi sposób"
	@echo "\n\"make run-cw8s / cw8d1 / cw8d2\" - kompiluje i uruchamia program do ćwiczenia 8 kolejno używając biblioteki statycznej / dzielonej / dzielonej dołączanej na drugi sposób"
	@echo "\n\"make all\" - kompiluje program i biblioteki na wszystkie możliwe powyżej sposoby jednocześnie"

$(LIB_STAT): $(LIB_OBJS_MQ)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

$(LIB_SHAR): $(LIB_OBJS_MQ)
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS_MQ)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

$(SERVER_EXEC_S) : $(SERVER_OBJ) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS)

$(CLIENT_EXEC_S) : $(CLIENT_OBJ) $(LIB_STAT)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS)

$(SERVER_EXEC_D1) : $(SERVER_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS) -Wl,-R $(LIB_DIR)

$(CLIENT_EXEC_D1) : $(CLIENT_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS) -Wl,-R $(LIB_DIR)

$(SERVER_EXEC_D2) : $(SERVER_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS)

$(CLIENT_EXEC_D2) : $(CLIENT_OBJ) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $< -L$(LIB_DIR) -l$(LIB_NAME) $(LD_LIBS)

.PHONY: cw8s run-cw8s

cw8s: $(EXECS_S)

run-cw8s: $(EXECS_S)
	$(RUN_SERVER) ./$(SERVER_EXEC_S) &
	sleep 1 ;
	$(RUN_CLIENT) ./$(CLIENT_EXEC_S) &
	sleep 1 ;
	$(RUN_CLIENT) ./$(CLIENT_EXEC_S) &
	
.PHONY: cw8d1 run-cw8d1

cw8d1: $(EXECS_D1)

run-cw8d1: $(EXECS_D1)
	$(RUN_SERVER) ./$(SERVER_EXEC_D1) &
	sleep 1 ;
	$(RUN_CLIENT) ./$(CLIENT_EXEC_D1) &
	sleep 1 ;
	$(RUN_CLIENT) ./$(CLIENT_EXEC_D1)

.PHONY: cw8d2 run-cw8d2

cw8d2: $(EXECS_D1)

run-cw8d2: $(EXECS_D2)
	$(DYNAMIC_LIB_EXPORT_PATH) \
	$(RUN_SERVER) ./$(SERVER_EXEC_D2) &
	sleep 1 ;
	$(DYNAMIC_LIB_EXPORT_PATH) \
	$(RUN_CLIENT) ./$(CLIENT_EXEC_D2) &
	sleep 1 ;
	$(DYNAMIC_LIB_EXPORT_PATH) \
	$(RUN_CLIENT) ./$(CLIENT_EXEC_D2) &

.PHONY: all
all: $(EXECS_S) $(EXECS_D1) $(EXECS_D2)

clean:
	rm  *.[ox] ./**/*.[ox]
	rm -rf ./$(LIB_DIR)
