#include <libchip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int lines[] = {19, 13, 6, 5};
    int SW_NUM = 1;

    ChipDevice *chip = chip_open(0);
    if (!chip)
        return EXIT_FAILURE;

    ChipLine *input_0 = chip_pin_mode(chip, lines[SW_NUM],
                                      PIN_MODE_OUTPUT, NULL);

    chip_close(chip);

    if (!input_0)
        return EXIT_FAILURE;

    while (1)
    {
        sleep(1);

        int value = chip_line_get_value(input_0, lines[SW_NUM]);

        printf("switch %d = %d\n", SW_NUM, value);
    }

    gpiod_line_request_release(input_0);

    return 0;
}

