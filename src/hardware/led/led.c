#include "platform.h"

#include "led.h"

typedef struct{
    GPIO_TypeDef* gpioPort;
    uint32_t    gpioPin;
    uint32_t    gpioClock;
}leds_t;

leds_t ledGreen = {
    .gpioPort = GPIOA,
    .gpioPin = LL_GPIO_PIN_5,
    .gpioClock = LL_AHB2_GRP1_PERIPH_GPIOA
};

static void led_init(leds_t *pLed);
static void led_on(leds_t *pLed);
static void led_off(leds_t *pLed);
static void led_toggle(leds_t *pLed);

void leds_init(void)
{
    led_init(&ledGreen);
}

void leds_greenLedSetState(uint8_t state)
{
    if(LEDS_STATE_ON == state)
    {
        led_on(&ledGreen);
    }
    else if(LEDS_STATE_TOGGLE == state)
    {
        led_toggle(&ledGreen);
    }
    else if(LEDS_STATE_OFF == state)
    {
        led_off(&ledGreen);
    }
}

static void led_init(leds_t *pLed)
{
    LL_GPIO_InitTypeDef LED_GPIO_User = {0};

    LL_AHB2_GRP1_EnableClock(pLed->gpioClock);

    LED_GPIO_User.Pin = pLed->gpioPin;
    LED_GPIO_User.Mode = LL_GPIO_MODE_OUTPUT;
    LED_GPIO_User.Pull = LL_GPIO_PULL_NO;

    LL_GPIO_Init(pLed->gpioPort, &LED_GPIO_User);
}

static void led_on(leds_t *pLed)
{
    LL_GPIO_SetOutputPin(pLed->gpioPort, pLed->gpioPin);
}

static void led_off(leds_t *pLed)
{
    LL_GPIO_ResetOutputPin(pLed->gpioPort, pLed->gpioPin);
}

static void led_toggle(leds_t *pLed)
{
    LL_GPIO_TogglePin(pLed->gpioPort, pLed->gpioPin);
}
