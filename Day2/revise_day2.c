#include <stdio.h>
#include <stdint.h>

// ===== TYPEDEF =====
typedef uint32_t Register;
typedef void (*CommandHandler)(Register*);
typedef uint8_t PinState;

// ===== BITWISE MACROS =====
#define SET_BIT(reg, bit)    ((reg) |= (1UL << (bit)))
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1UL << (bit)))
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1UL << (bit)))
#define READ_BIT(reg, bit)   (((reg) >> (bit)) & 1UL)
#define SET_MASK(reg, mask)  ((reg) |= (mask))
#define CLEAR_MASK(reg, mask) ((reg) &= ~(mask))

#define DELAY_MS(x) printf("Delay: %d ms\n", x);

// ===== PREPROCESSOR =====
#define DEBUG_MODE  1
#define LED_PIN     5
#define BUTTON_PIN  2

// ===== HÀM CALLBACK =====
void led_on(Register *reg)  { SET_BIT(*reg, LED_PIN); }
void led_off(Register *reg) { CLEAR_BIT(*reg, LED_PIN); }
void led_toggle(Register *reg) { TOGGLE_BIT(*reg, LED_PIN); }

void blink_led(PinState *pin) {
    TOGGLE_BIT(*pin, 3);
    printf("Pin: 0x%02X\n", *pin);

    DELAY_MS(500);
}

int main() {
    Register gpio = 0x00;
    CommandHandler cmd;
    PinState led = 0x00;

    // Test LED ON
    cmd = led_on;
    cmd(&gpio);
    printf("LED ON:  0x%02lX (bit %d = %lu)\n", gpio, LED_PIN, READ_BIT(gpio, LED_PIN));

    // Test LED OFF
    cmd = led_off;
    cmd(&gpio);
    printf("LED OFF: 0x%02lX (bit %d = %lu)\n", gpio, LED_PIN, READ_BIT(gpio, LED_PIN));

    // Test LED TOGGLE
    cmd = led_toggle;
    cmd(&gpio);
    printf("TOGGLE:  0x%02lX (bit %d = %lu)\n", gpio, LED_PIN, READ_BIT(gpio, LED_PIN));
    cmd(&gpio);
    printf("TOGGLE:  0x%02lX (bit %d = %lu)\n", gpio, LED_PIN, READ_BIT(gpio, LED_PIN));

    // Test BUTTON (mô phỏng)
    SET_BIT(gpio, BUTTON_PIN);
    printf("BUTTON:  0x%02lX (bit %d = %lu)\n", gpio, BUTTON_PIN, READ_BIT(gpio, BUTTON_PIN));

    // Test SET_MASK
    SET_MASK(gpio, 0xF0);
    printf("MASK:    0x%02lX\n", gpio);

    // Test CLEAR_MASK
    CLEAR_MASK(gpio, 0xF0);
    printf("CLEAR:   0x%02lX\n", gpio);

    for (int i = 0; i < 3; i++) {
        blink_led(&led);

    }

#if DEBUG_MODE
    printf("\n[DEBUG] Final register: 0x%02lX\n", gpio);
#endif

    return 0;
}