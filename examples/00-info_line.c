/* SPDX-License-Identifier: GPL-2.0-or-later
 * SPDX-FileCopyrightText: 2023 Kent Gibson <warthog618@gmail.com>
 *
 * Minimal example of reading the info for a line. */

#include <libchip.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    ChipDevice *chip = chip_open(0);
    if (!chip)
    {
        fprintf(stderr, "failed to open chip: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    int line_offset = 3;
    struct gpiod_line_info *info;

    info = gpiod_chip_get_line_info(chip, line_offset);
    if (!info)
    {
        fprintf(stderr, "failed to read info: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    const char *name = gpiod_line_info_get_name(info);
    if (!name)
        name = "unnamed";

    const char *consumer = gpiod_line_info_get_consumer(info);
    if (!consumer)
        consumer = "unused";

    const char *dir =
        (gpiod_line_info_get_direction(info) ==
         GPIOD_LINE_DIRECTION_INPUT) ?
            "input" :
            "output";

    printf("line %3d: %12s %12s %8s %10s\n",
           gpiod_line_info_get_offset(info),
           name, consumer, dir,
           gpiod_line_info_is_active_low(info)
               ? "active-low" : "active-high");

    gpiod_line_info_free(info);
    gpiod_chip_close(chip);

    return EXIT_SUCCESS;
}

