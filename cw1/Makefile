CFLAGS := -pedantic -Wall -std=c99
LFLAGS := $(CFLAGS)
CO     := gcc
LD     := $(CO)

RUN_PREFIX := run-
NAMES := $(patsubst %.c,%,$(wildcard *.c))
OBJS := $(patsubst %,%.o,$(NAMES))
EXECS := $(patsubst %,%.x,$(NAMES))
RUN_NAMES := $(patsubst %,$(RUN_PREFIX)%,$(NAMES))

.PHONY: help
help:
	@echo "make all - kompiluje wszystkie programy"
	@echo "make print - wypisuje nazwy programów do skompilowania"
	@echo "make cw1x - kompiluje program do ćwiczenia 1, podpunkt x, gdzie x od a do e"
	@echo "make run-cw1x - uruchamia program do ćwiczenia 1, podpunkt x, gdzie x od a do e"
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

.PHONY: $(RUN_NAMES)

$(RUN_NAMES): %:
	./$(subst $(RUN_PREFIX),,$@).x

.PHONY: clean
clean:
	rm *.o *.x