# CANBusServer Build
COMP_OBJDIR=./CANBusServer/output
COMP_OBJNAMES=CANBusLinkedList.o
COMP_OBJS=$(addprefix $(COMP_OBJDIR)/,$(COMP_OBJNAMES))
SRC_PATH=./CANBusServer/src
SRC=$(wildcard $(SRC_PATH)/*.c)

$(COMP_OBJDIR)/%.o: $(SRC_PATH)/CANBusLinkedList.c
	$(CC) $(CFLAGS) -o $@ -c $^