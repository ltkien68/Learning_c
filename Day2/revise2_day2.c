#include <stdio.h>
#include <stdint.h>

typedef uint8_t Register;

typedef enum {
    LED_ON,
    LED_OFF
} LED_STATUS;

typedef enum {
    OK,
    BUTTON_ERROR,
    LED_ERROR,
} SYSTEM_STATUS;

#define LED1_PIN    3
#define LED2_PIN    1
#define BUTTON_PIN  0

#define SET_BIT(reg, bit)       ((reg) |= (1UL << (bit)))
#define CLEAR_BIT(reg, bit)     ((reg) &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit)    ((reg) ^= (1UL << (bit)))
#define READ_BIT(reg, bit)      (((reg) >> (bit)) & 1UL)

typedef void (*LedCommand)(Register*);

LED_STATUS led1_status = LED_OFF;
LED_STATUS led2_status = LED_OFF;

void led1_on(Register* reg) {
    led1_status = LED_ON;
    SET_BIT(*reg, LED1_PIN);
}

void led1_off(Register* reg) {
    led1_status = LED_OFF;
    CLEAR_BIT(*reg, LED1_PIN);
}

void led2_on(Register* reg) {
    led2_status = LED_ON;
    SET_BIT(*reg, LED2_PIN);
}

void led2_off(Register* reg) {
    led2_status = LED_OFF;
    CLEAR_BIT(*reg, LED2_PIN);
}

SYSTEM_STATUS systemCheck(Register reg) {
    if (led1_status != LED_ON || led2_status != LED_ON) {
        return LED_ERROR;
    }
    if (!READ_BIT(reg, BUTTON_PIN)) {
        return BUTTON_ERROR;
    }
    return OK;
}

int main() {
    Register gpio = 0x00;
    LedCommand cmd;
    SYSTEM_STATUS sys;

    cmd = led1_on;
    cmd(&gpio);
    printf("LED1 ON: 0x%02X\n", gpio);

    cmd = led2_on;
    cmd(&gpio);
    printf("LED2 ON: 0x%02X\n", gpio);

    SET_BIT(gpio, BUTTON_PIN);
    printf("BUTTON: 0x%02X\n", gpio);

    sys = systemCheck(gpio);
    if (sys == LED_ERROR) {
        printf("LED error!\n");
    } else if (sys == BUTTON_ERROR) {
        printf("BUTTON error!\n");
    } else {
        printf("OK\n");
    }

    cmd = led1_off;
    cmd(&gpio);
    printf("LED1 OFF: 0x%02X\n", gpio);

    sys = systemCheck(gpio);
    if (sys == LED_ERROR) {
        printf("LED error!\n");
    }

    return 0;
}

