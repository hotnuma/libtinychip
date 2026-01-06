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

    ChipDevice *chip = chip_open(0);
    if (!chip)
        return EXIT_FAILURE;

    ChipLine *input_0 = chip_set_input(chip, lines[SW_NUM],
                                       GPIOD_LINE_BIAS_PULL_UP, NULL);

    chip_close(chip);

    if (!input_0)
        return EXIT_FAILURE;

    while (_loop)
    {
        sleep(1);

        int value = chip_line_get_value(input_0, lines[SW_NUM]);

        printf("switch %d = %d\n", SW_NUM, value);
    }

    chip_line_release(input_0);

    return 0;
}


