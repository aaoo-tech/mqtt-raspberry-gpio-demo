#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <mosquitto.h>
#include "json.h"

#define mqtt_host "iot.aaoo-tech.com"
#define mqtt_port 1883

static int run = 1;

void connect_callback(struct mosquitto *mosq, void *obj, int result) {
  printf("connect callback, rc=%d\n", result);
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {

  char* message_content = (char *) message->payload;
  json_char* json = (json_char *) message_content;
  json_value* value = json_parse(json, message->payloadlen);

  char* action = value->u.object.values[0].value->u.string.ptr;
  printf("%s\n", action);

  json_value_free(value);
}

int main(int argc, char* argv[]) {
  uint8_t reconnect = true;

  char clientid[24];
  struct mosquitto *mosq;

  int rc = 0;

  mosquitto_lib_init();

  memset(clientid, 0, 24);
  snprintf(clientid, 23, "mysql_log_%d", getpid());
  mosq = mosquitto_new(clientid, true, 0);

  if (mosq) {
    mosquitto_connect_callback_set(mosq, connect_callback);
    mosquitto_message_callback_set(mosq, message_callback);

    rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);
    mosquitto_subscribe(mosq, NULL, "/yun/router/cloudriver-router/cloudriver-device", 0);

    while (run) {
      rc = mosquitto_loop(mosq, -1, 1);

      if (run && rc) {
        printf("connection error!\n");
        sleep(10);
        mosquitto_reconnect(mosq);
      }
    }

    mosquitto_destroy(mosq);
  }

  mosquitto_lib_cleanup();

  return rc;
}
