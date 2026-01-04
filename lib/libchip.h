#ifndef LIBCHIP_H
#define LIBCHIP_H

#include <gpiod.h>

typedef struct gpiod_chip ChipDevice;
typedef struct gpiod_line_request ChipLine;
ChipDevice* chip_open(int channel);
ChipLine* chip_set_input(ChipDevice *chip, unsigned int line,
                         int bias, const char *consumer);
#define chip_close gpiod_chip_close

#define chip_line_get_value gpiod_line_request_get_value
#define chip_line_release gpiod_line_request_release

#endif // LIBCHIP_H

