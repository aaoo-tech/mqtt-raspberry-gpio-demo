#include <stdio.h>

#include "MQTTClient.h"
#include "gpio.h"

#include "json.h"
#include <sys/stat.h>

#include <signal.h>
#include <memory.h>
#include <sys/time.h>

#include "test.h"

void cfinish(int sig) {
  signal(SIGINT, NULL);
  toStop = 1;
}

void message_arrived(MessageData* md) {
  MQTTMessage* message = md->message;
  char* message_content = (char*) message->payload;

  json_char* json = (json_char *) message_content;
  json_value* value = json_parse(json, message->payloadlen);

  char* action = value->u.object.values[0].value->u.string.ptr;

  if (strcmp(action, "turnon") == 0) {
    GPIO_SET = 1 << RP_GPIO_PORT_0;
  } else {
    GPIO_CLR = 1 << RP_GPIO_PORT_0;
  }

  json_value_free(value);
  // printf("%.*s%s", (int)message->payloadlen, (char*)message->payload, (char*) "\n");
  //fflush(stdout);
}

void read_config_file() {
  FILE *fp;
  char* filename = "../config/config.json";
  struct stat filestatus;
  char* file_contents;
  int file_size;

  if (stat(filename, &filestatus) != 0) {
    printf("cannot load file\n");
    exit(-1);
  }

  file_size = filestatus.st_size;
  file_contents = (char*) malloc (filestatus.st_size);

  fp = fopen(filename, "rt");
  if (fp == NULL) {
    printf("cannot load file\n");
    fclose(fp);
    free(file_contents);
    exit(-1);
  }

  if (fread(file_contents, file_size, 1, fp) != 1) {
    printf("cannot load file\n");
    fclose(fp);
    free(file_contents);
    exit(-1);
  }

  fclose(fp);

  json_char* json;
  json_value* value;
  json = (json_char *) file_contents;
  value = json_parse(json, file_size);

  if (value == NULL) {
    free(file_contents);
    exit(-1);
  }

  host = value->u.object.values[0].value->u.string.ptr;
  port = value->u.object.values[1].value->u.integer;
  uuid = value->u.object.values[2].value->u.string.ptr;
  username = value->u.object.values[3].value->u.string.ptr;
  password = value->u.object.values[4].value->u.string.ptr;
}

void init_rpi_gpio() {
  _rp_setup_id();

  INP_GPIO(RP_GPIO_PORT_0);
  OUT_GPIO(RP_GPIO_PORT_0);
}

int main(int argc, char** argv) {

  read_config_file();
  init_rpi_gpio();

  int rc;
  unsigned char buf[100];
  unsigned char readbuf[100];

  Network n;
  Client c;

  signal(SIGINT, cfinish);
  signal(SIGTERM, cfinish);

  NewNetwork(&n);
  ConnectNetwork(&n, host, port);
  MQTTClient(&c, &n, 1000, buf, 100, readbuf, 100);

  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
  data.willFlag = 0;
  data.MQTTVersion = 3;
  data.clientID.cstring = uuid;
  data.username.cstring = username;
  data.password.cstring = password;

  data.keepAliveInterval = 10;
  data.cleansession = 1;
  printf("Connecting to %s %d\n", host, port);

  rc = MQTTConnect(&c, &data);

  rc = MQTTSubscribe(&c, (char *) "/yun/router/cloudriver-router/cloudriver-device", QOS2, message_arrived);

  while (! toStop) {
    MQTTYield(&c, 1000);
  }

  return 0;
}
