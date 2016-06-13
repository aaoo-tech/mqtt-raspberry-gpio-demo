#ifndef __AAOO_RP_GPIO_
#define __AAOO_RP_GPIO_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(_rp_gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(_rp_gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(_rp_gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET *(_rp_gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(_rp_gpio+10) // clears bits which are 1 ignores bits which are 0
 
#define GET_GPIO(g) (*(_rp_gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(_rp_gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(_rp_gpio+38) // Pull up/pull down clock

int _rp_mem_fd;
void * _rp_gpio_map;
volatile unsigned * _rp_gpio;

#define RP_GPIO_PORT_0 4
#define RP_GPIO_PORT_1 7
#define RP_GPIO_PORT_2 8
#define RP_GPIO_PORT_3 9
#define RP_GPIO_PORT_4 10
#define RP_GPIO_PORT_5 11
#define RP_GPIO_PORT_6 17
#define RP_GPIO_PORT_7 18
#define RP_GPIO_PORT_8 22
#define RP_GPIO_PORT_9 24
#define RP_GPIO_PORT_10 25
#define RP_GPIO_PORT_11 26
#define RP_GPIO_PORT_12 27

void _rp_setup_id();

#endif
