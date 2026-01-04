#ifndef LIBCHIP_H
#define LIBCHIP_H

#include <gpiod.h>

#define PIN_MODE_INPUT 0
#define PIN_MODE_INPUT_PULLUP 2
#define PIN_MODE_INPUT_PULLDOWN 4
#define PIN_MODE_OUTPUT 1

typedef struct gpiod_chip ChipDevice;
ChipDevice* chip_open(int channel);
#define chip_close gpiod_chip_close

typedef struct gpiod_line_request ChipLine;
#define chip_line_get_value gpiod_line_request_get_value
#define chip_line_release gpiod_line_request_release

ChipLine* chip_pin_mode(ChipDevice *chip, unsigned int line,
                        int flags, const char *consumer);

#endif // LIBCHIP_H

