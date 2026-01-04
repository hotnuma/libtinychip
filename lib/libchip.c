#include <libchip.h>
#include <stdio.h>

struct gpiod_chip* chip_open(int channel)
{
    char chip_path[32];
    sprintf(chip_path, "/dev/gpiochip%d", channel);

    return gpiod_chip_open(chip_path);
}

struct gpiod_line_request* chip_line_request(struct gpiod_chip *chip,
                                             unsigned int offset,
                                             enum gpiod_line_direction direction,
                                             enum gpiod_line_bias bias,
                                             const char *consumer)
{
    struct gpiod_line_request *request = NULL;

    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    if (!settings)
        return NULL;

    if (direction != GPIOD_LINE_DIRECTION_AS_IS)
        gpiod_line_settings_set_direction(settings, direction);
    if (bias != GPIOD_LINE_BIAS_AS_IS)
        gpiod_line_settings_set_bias(settings, bias);

    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    if (!line_cfg)
        goto free_settings;

    int ret = gpiod_line_config_add_line_settings(line_cfg,
                                                  &offset, 1, settings);
    if (ret)
        goto free_line_config;

    struct gpiod_request_config *req_cfg = NULL;

    if (consumer)
    {
        req_cfg = gpiod_request_config_new();
        if (!req_cfg)
            goto free_line_config;

        gpiod_request_config_set_consumer(req_cfg, consumer);
    }

    request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);

    gpiod_request_config_free(req_cfg);

free_line_config:
    gpiod_line_config_free(line_cfg);

free_settings:
    gpiod_line_settings_free(settings);

    return request;
}

