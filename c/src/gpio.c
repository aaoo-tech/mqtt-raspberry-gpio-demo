#include "gpio.h"

void _rp_setup_id() {
  if ((_rp_mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
    printf("can't open /dev/mem \n");
    exit(-1);
  }

  _rp_gpio_map = mmap(
    NULL,
    BLOCK_SIZE,
    PROT_READ | PROT_WRITE,
    MAP_SHARED,
    _rp_mem_fd,
    GPIO_BASE
  );

  close(_rp_mem_fd);

  if (_rp_gpio_map == MAP_FAILED) {
    printf("mmap error %d\n", (int) _rp_gpio_map);
    exit(-1);
  }

  _rp_gpio = (volatile unsigned *) _rp_gpio_map;
}
