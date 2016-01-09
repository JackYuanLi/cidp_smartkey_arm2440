OBJ=smartkey.o buzzer_ctrl.o led_ctrl.o
CC=arm-linux-gcc
CFLAGS=-c


smartkey:$(OBJ)
		$(CC) $^ -o $@
smartkey.o: smartkey.c buzzer_ctrl.h led_ctrl.h
		$(CC) $(CFLAGS) $< -o $@
buzzer_ctrl.o:buzzer_ctrl.c buzzer_ctrl.h
		$(CC) $(CFLAGS) $< -o $@
led_ctrl.o:led_ctrl.c led_ctrl.h
		$(CC) $(CFLAGS) $< -o $@
clean:
		rm -f smartkey *.o
