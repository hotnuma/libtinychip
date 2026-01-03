#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <libchip.h>
#include <errno.h>
#include <string.h>

int main()
{
    int lines[] = {19, 13, 6, 5};
    int SW_NUM = 1;

    struct gpiod_chip *chip = chip_open(0);
    if (!chip)
        return EXIT_FAILURE;

    struct gpiod_line_request *input_0 =
        chip_line_request(chip, lines[SW_NUM], "get-line-value");

    gpiod_chip_close(chip);

    if (!input_0)
        return EXIT_FAILURE;

    while (1)
    {
        sleep(1);

        int value = gpiod_line_request_get_value(input_0, lines[SW_NUM]);

        printf("switch %d = %d\n", SW_NUM, value);
    }

    gpiod_line_request_release(input_0);

    return 0;
}


