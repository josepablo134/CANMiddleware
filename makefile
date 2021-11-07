# General Config
CC=gcc
INC_PATHS= ./CANBusServer/include ./CANBusServer/cfg
INCLUDE=$(addprefix -I, $(INC_PATHS))
CFLAGS=-Wall $(INCLUDE) -g

include component.mk

# Final Binary Build
OBJDIR=./output
OBJNAMES=main.o
OBJS=$(addprefix $(OBJDIR)/,$(OBJNAMES))
BINARY=main.exec
OUTDIR=./output

.PHONY: all
all: $(OBJS) $(COMP_OBJS)
	$(CC) $(CFLAGS) $^ -o $(OUTDIR)/$(BINARY)

$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	rm $(OUTDIR)/main.exec $(COMP_OBJS) $(OBJS)