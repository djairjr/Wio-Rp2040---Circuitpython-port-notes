# Wio-Rp2040---Circuitpython-port-notes
Taking some notes in order to port Circuitpython to Wio RP2040

Trying to figure out which interface is connected to ESP8285 - appears to be SPI

User in forum informs that Micropython port for this board is same as this version:
https://github.com/IsQianGe/rp2040-spi

in this Micropython port, this pins are described: (file machine_spi.c)
#define DEFAULT_SPI_BAUDRATE    (200000)
#define DEFAULT_SPI_POLARITY    (0)
#define DEFAULT_SPI_PHASE       (0)
#define DEFAULT_SPI_BITS        (8)
#define DEFAULT_SPI_FIRSTBIT    (SPI_MSB_FIRST)
#define DEFAULT_SPI0_SCK        (2)
#define DEFAULT_SPI0_MOSI       (3)
#define DEFAULT_SPI0_MISO       (4)
#define DEFAULT_SPI1_SCK        (10)
#define DEFAULT_SPI1_MOSI       (11)
#define DEFAULT_SPI1_MISO       (8)

#define SPI_HANDSHARK   21
#define SPI_CS   9

# From Adafruit_CircuitPython_ESP32SPI library, I need three pins...
esp32_cs = DigitalInOut(board.ESP_CS) // Maybe SPI_CS
esp32_ready = DigitalInOut(board.ESP_BUSY) // Maybe SPI_HANDSHARK (handshake)
esp32_reset = DigitalInOut(board.ESP_RESET) // Active Low which Pin?

# In https://github.com/IsQianGe/rp2040-spi file mod_wifi_spi.c

//esp8285 power on
			mp_hal_pin_output(21); // SPI_HANDSHARK?
			mp_hal_pin_output(22);
			mp_hal_pin_output(24);
			mp_hal_pin_output(25);
			mp_hal_pin_output(SPI_CS); // Pin 9
      
			gpio_put(21,1); // Some of this pins are connected to ESP8285 CHIP_EN pin... Maybe not 21
			gpio_put(24,1); // Some of this pins are connected to ESP8285 XPD_DCDC pin...
			gpio_put(22,1); // Some of this pins are connected to ESP8285 EXT_RSTB pin
			gpio_put(SPI_CS,0);
			gpio_put(25,0);
			mp_hal_pin_input(SPI_HANDSHARK); // This pin is checked in order to see if 8285 is ready LOW if ready
			gpio_put(SPI_CS,1);
      
  // esp8285 power down
			mp_hal_pin_output(21);
			mp_hal_pin_output(22);
			mp_hal_pin_output(24);
      mp_hal_pin_output(25); //?
      
			gpio_put(21,0);
			gpio_put(24,0);
			gpio_put(22,0);
      gpio_put(25,1); // ?
