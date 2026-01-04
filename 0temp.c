
#if 0

#define PIN_MODE_INPUT 0
#define PIN_MODE_INPUT_PULLUP 2
#define PIN_MODE_INPUT_PULLDOWN 4
#define PIN_MODE_OUTPUT 1

ChipLine* chip_pin_mode(ChipDevice *chip, unsigned int line,
                        int flags, const char *consumer);


ChipLine* chip_pin_mode(ChipDevice *chip, unsigned int line,
                        int flags, const char *consumer)
{
    struct gpiod_line_request *request = NULL;

    struct gpiod_line_settings *settings = gpiod_line_settings_new();
    if (!settings)
        return NULL;

    switch (flags)
    {
    case PIN_MODE_INPUT:
        gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);
        gpiod_line_settings_set_bias(settings, GPIOD_LINE_BIAS_PULL_UP);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);
        gpiod_line_settings_set_bias(settings, GPIOD_LINE_BIAS_PULL_DOWN);
        break;
    case PIN_MODE_OUTPUT:
        gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
        break;
    }

    struct gpiod_line_config *line_cfg = gpiod_line_config_new();
    if (!line_cfg)
        goto free_settings;

    int ret = gpiod_line_config_add_line_settings(line_cfg,
                                                  &line, 1, settings);
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

#endif


