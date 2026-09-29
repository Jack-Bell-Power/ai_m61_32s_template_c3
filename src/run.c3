module ai_m61_32s_template;

extern fn void board_init();

extern fn void* bflb_device_get_by_name(char* name);

extern fn void bflb_gpio_init(
    void* gpio,
    int pin,
    int mode
);

extern fn void bflb_gpio_set(
    void* gpio,
    int pin
);

extern fn void bflb_gpio_reset(
    void* gpio,
    int pin
);

extern fn void bflb_mtimer_delay_ms(
    int ms
);

const int GPIO_PIN_12 = 12;
const int GPIO_PIN_14 = 14;
const int GPIO_PIN_15 = 15;

const int GPIO_OUTPUT = 1 << 6;
const int GPIO_PULLUP = 1 << 9;
const int GPIO_SMT_EN = 1 << 11;
const int GPIO_DRV_0 = 0;

fn int run() @export("run")
{
    board_init();

    void* gpio = bflb_device_get_by_name("gpio");

    int config =
        GPIO_OUTPUT |
        GPIO_PULLUP |
        GPIO_SMT_EN |
        GPIO_DRV_0;

    bflb_gpio_init(gpio, GPIO_PIN_12, config);
    bflb_gpio_init(gpio, GPIO_PIN_14, config);
    bflb_gpio_init(gpio, GPIO_PIN_15, config);

    while (true)
    {
        // GPIO 12
        bflb_gpio_set(gpio, GPIO_PIN_12);
        bflb_mtimer_delay_ms(500);
        bflb_gpio_reset(gpio, GPIO_PIN_12);
        bflb_mtimer_delay_ms(500);

        // GPIO 14
        bflb_gpio_set(gpio, GPIO_PIN_14);
        bflb_mtimer_delay_ms(500);
        bflb_gpio_reset(gpio, GPIO_PIN_14);
        bflb_mtimer_delay_ms(500);

        // GPIO 15
        bflb_gpio_set(gpio, GPIO_PIN_15);
        bflb_mtimer_delay_ms(500);
        bflb_gpio_reset(gpio, GPIO_PIN_15);
        bflb_mtimer_delay_ms(500);
    }
}