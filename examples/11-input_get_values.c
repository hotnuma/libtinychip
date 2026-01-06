/* SPDX-License-Identifier: GPL-2.0-or-later
 * SPDX-FileCopyrightText: 2023 Kent Gibson <warthog618@gmail.com>
 * Minimal example of reading a single line. */

#include <libchip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int _loop = 1;

void sigint_handler(int sig)
{
    (void) sig;
    _loop = 0;
}

#define IN_COUNT 4

int main()
{
    signal(SIGINT, sigint_handler);

    unsigned int lines[IN_COUNT] = {19, 13, 6, 5};
    int values[IN_COUNT] = {0};

    ChipDevice *chip = chip_open(0);
    if (!chip)
        return EXIT_FAILURE;

    ChipLine *inputs = chip_set_input_array(chip, lines, IN_COUNT,
                                            GPIOD_LINE_BIAS_PULL_UP, NULL);

    chip_close(chip);

    if (!inputs)
        return EXIT_FAILURE;

    while (_loop)
    {
        sleep(1);

        chip_line_get_values(inputs, values);

        for (int i = 0; i < IN_COUNT; ++i)
        {
            printf("switch %d = %d\n", i, values[i]);
        }
    }

    chip_line_release(inputs);

    return 0;
}

