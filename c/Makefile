CFLAGS += -Wall -pedantic -std=c99

all: bin/test

clean:
	rm src/*.o bin/*

src/gpio.o: src/gpio.c src/gpio.h
src/MQTTPacket.o: src/MQTTPacket.c src/MQTTPacket.h
src/MQTTClient.o: src/MQTTClient.c src/MQTTClient.h
src/MQTTConnectClient.o: src/MQTTConnectClient.c
src/MQTTConnectServer.o: src/MQTTConnectServer.c
src/MQTTDeserializePublish.o: src/MQTTDeserializePublish.c
src/MQTTFormat.o: src/MQTTFormat.c src/MQTTFormat.h
src/MQTTLinux.o: src/MQTTLinux.c src/MQTTLinux.h
src/MQTTSerializePublish.o: src/MQTTSerializePublish.c
src/MQTTSubscribe.o: src/MQTTSubscribe.c src/MQTTSubscribe.o
src/MQTTSubscribeClient.o: src/MQTTSubscribeClient.c
src/MQTTSubscribeServer.o: src/MQTTSubscribeServer.c
src/MQTTUnsubscribeClient.o: src/MQTTUnsubscribeClient.c
src/MQTTUnsubscribeServer.o: src/MQTTUnsubscribeServer.c
src/json.o: src/json.c src/json.h
src/test.o: src/test.c src/test.h

bin/test: src/json.o src/test.o src/gpio.o src/MQTTPacket.o src/MQTTClient.o src/MQTTConnectClient.o src/MQTTConnectServer.o src/MQTTDeserializePublish.o src/MQTTFormat.o src/MQTTLinux.o src/MQTTSerializePublish.o src/MQTTSubscribeClient.o src/MQTTSubscribeServer.o src/MQTTUnsubscribeClient.o src/MQTTUnsubscribeServer.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o bin/test src/*.o -lm