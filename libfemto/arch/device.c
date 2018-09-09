// See LICENSE for license details.

#include "femto.h"

void register_console(console_device_t *dev)
{
    console_dev = dev;
    if (dev->init) {
        dev->init();
    }
}

void register_poweroff(poweroff_device_t *dev)
{
    poweroff_dev = dev;
    if (dev->init) {
        dev->init();
    }
}

int getchar()
{
    return console_dev->getchar();
}

int putchar(int ch)
{
    return console_dev->putchar(ch);
}

void poweroff()
{
    poweroff_dev->poweroff();
}

static int default_getchar()
{
    asm volatile("ebreak");
    return 0;
}

static int default_putchar(int ch)
{
    asm volatile("ebreak");
    return 0;
}

static __attribute__((noreturn)) void default_poweroff()
{
    asm volatile("ebreak");
    while (1) {
        asm volatile("" : : : "memory");
    }
}

console_device_t console_none = {
    NULL,
    default_getchar,
    default_putchar
};

poweroff_device_t poweroff_none = {
    NULL,
    default_poweroff,
};

console_device_t *console_dev = &console_none;
poweroff_device_t *poweroff_dev = &poweroff_none;
