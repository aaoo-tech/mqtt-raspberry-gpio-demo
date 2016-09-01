CFLAGS += -Wall -pedantic -std=c99

all: aaoo_openwrt_mqtt

clean:
	rm *.o

mos_mqtt.o: mos_mqtt.c

aaoo_openwrt_mqtt: mos_mqtt.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o aaoo_openwrt_mqtt *.c -lmosquitto