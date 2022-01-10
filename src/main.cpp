#include <Arduino.h>

#include "pico/stdlib.h"
#include "pico/stdio_uart.h"

void setup();
void loop();

byte buffer_arduino;
//String buffer_arduino_String;
void setup_arduino_way(){
  // Init Serial
  Serial1.setTX(12);
  Serial1.setRX(13);
  // Start serial
  Serial1.begin(115200);
}
void read_arduino_way(){
  if (Serial1.available()) {
    buffer_arduino = Serial1.read();
//    buffer_arduino_String = Serial1.readString();
    Serial1.write(buffer_arduino);
//    Serial1.print(buffer_arduino_String);
//    if (buffer_arduino == "0") {
//    }
    if (buffer_arduino == '\r' || buffer_arduino == '\n') {
      Serial1.print("\n\r");
    }
  }
}

char buffer_pico;
void setup_pico_way(){
  stdio_uart_init_full(uart0, 115200, 12, 13);
}
void read_pico_way(){
  while (true) {
    if (uart_is_readable(uart0)) {
      buffer_pico = getchar();
      printf("%c", buffer_pico);
      if (buffer_pico == '\r' || buffer_pico == '\n') {
        printf("\n\r");
      }
    }
    printf("\r\n");
    sleep_ms(10);
  }
}

void setup() {
//  setup_arduino_way();
  setup_pico_way();
}

void loop() {
//  read_arduino_way();
  read_pico_way();
}