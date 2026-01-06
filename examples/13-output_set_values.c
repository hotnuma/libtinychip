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

#define OUT_COUNT 4

int main()
{
    signal(SIGINT, sigint_handler);

    unsigned int lines[OUT_COUNT] = {19, 13, 6, 5};
    int values[OUT_COUNT] = {0};

    ChipDevice *chip = chip_open(0);
    if (!chip)
        return EXIT_FAILURE;

    ChipLine *outputs = chip_set_output_array(chip, lines, values, OUT_COUNT, NULL);

    chip_close(chip);

    if (!outputs)
        return EXIT_FAILURE;

    while (_loop)
    {
        sleep(1);

        for (int i = 0; i < OUT_COUNT; ++i)
        {
            values[i] = (values[i] == 1 ? 0 : 1);
            printf("output %d = %d\n", i, values[i]);
        }

        chip_line_set_values(outputs, values);
    }

    chip_line_release(outputs);

    return 0;
}

