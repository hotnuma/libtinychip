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

int main()
{
    signal(SIGINT, sigint_handler);

    int lines[] = {19, 13, 6, 5};
    int SW_NUM = 1;
    int value = 0;

    ChipDevice *chip = chip_open(0);
    if (!chip)
        return EXIT_FAILURE;

    ChipLine *output_0 = chip_set_output(chip, lines[SW_NUM],
                                         value, NULL);
    chip_close(chip);

    if (!output_0)
        return EXIT_FAILURE;

    while (_loop)
    {
        sleep(1);

        value = (value == 1 ? 0 : 1);
        chip_line_set_value(output_0, lines[SW_NUM], value);

        printf("output %d = %d\n", SW_NUM, value);
    }

    chip_line_release(output_0);

    return 0;
}


