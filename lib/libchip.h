#ifndef LIBCHIP_H
#define LIBCHIP_H

#include <gpiod.h>

struct gpiod_chip* chip_open(int channel);
struct gpiod_line_request* chip_line_request(struct gpiod_chip *chip,
                                             unsigned int offset,
                                             enum gpiod_line_direction direction,
                                             enum gpiod_line_bias bias,
                                             const char *consumer);

#endif // LIBCHIP_H

