#include <stdio.h>
#include <stdlib.h>

#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define SERVO_PIN 22

void config_servo();
void set_servo_position(uint16_t cycle);

static volatile int pulse_width = 500;
uint servo_slice_num;

int main() {
  stdio_init_all();
  config_servo();

  while (true) {
    set_servo_position(2400);
    set_servo_position(1470);
    set_servo_position(500);
    smooth_moviment();
    sleep_ms(1000);
  }
}

void config_servo() {
  // Inicializa o hardware GPIO
  gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);

  // Configura o PWM para 50Hz (20ms de período)
  servo_slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
  pwm_set_clkdiv(servo_slice_num, 2.0);
  // Valor de wrap para 50Hz (1/50Hz = 20ms)
  pwm_set_wrap(servo_slice_num, 2000);
  pwm_set_gpio_level(SERVO_PIN, 500);
  pwm_set_enabled(servo_slice_num, true);
}

void set_servo_position(uint16_t cycle) {
  pwm_set_gpio_level(SERVO_PIN, cycle);
  sleep_ms(5000);
}

void smooth_moviment() {
  for (int i = 500; i <= 2400; i++) {
    pwm_set_gpio_level(SERVO_PIN, i);
    sleep_ms(10);
  }

  for (int i = 2400; i >= 500; i--) {
    pwm_set_gpio_level(SERVO_PIN, i);
    sleep_ms(10);
  }
}