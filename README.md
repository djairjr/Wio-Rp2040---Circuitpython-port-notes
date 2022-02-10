# Wio-Rp2040---Circuitpython-port-notes
Taking some notes in order to port Circuitpython to Wio RP2040

Trying to figure out which interface is connected to ESP8285 - appears to be SPI1

# On ESP8285 Datasheet
ESP8285 features 17 GPIOs, all of which can be assigned to support various functions of LED lights and buttons. Definitions of some GPIOs that are assigned with certain functions
in demo application design are shown as below.

Pin Name	Pin Num		IO	Function Name
MTCK 		12		IO13	Button (Reset)
GPIO0		15		IO0	Wi-Fi Light
MTDI		10		IO12	Link Light

Altogether three interfaces have been defined, one is for the button (INPUT), while the other two are for LED light (OUTPUTS). Generally, MTCK is used to control the reset button, GPIO0 is used as a signal to indicate the Wi-Fi working state, MTDI is used as a signal light to indicate communication status between the device and the server.

# Other Special Pins on ESP8285
EXT_RSTB  	INPUT	External reset signal (ACTIVE LOW)
XPD_DCDC 	I/O 	Deep-sleep wakeup (need to be connected to EXT_RSTB); GPIO16.
CHIP_PU 	I	Chip Enable
			High: On, chip works properly
			Low: Off, small current consumed

# From Adafruit_CircuitPython_ESP32SPI library, I need three pins...
esp32_cs 	= DigitalInOut(board.ESP_CS) 	// Probably SPI_CS - RP2040 pin GP9
esp32_ready 	= DigitalInOut(board.ESP_BUSY) 	// Defined as INPUT. Maybe related to pin 21? ACTIVE LOW. Could be ESP8285 GPIO0?
esp32_reset 	= DigitalInOut(board.ESP_RESET) // Defined as OUTPUT. Could be connected to ESP8285 MTCK pin?

User in forum informs that Micropython port for this board is same as this version:
https://github.com/IsQianGe/rp2040-spi

# So, i want to check if there is any indication of connections in code...

in this Micropython port, this pins are described: (file machine_spi.c)
#define DEFAULT_SPI_BAUDRATE    (200000)
#define DEFAULT_SPI_POLARITY    (0)
#define DEFAULT_SPI_PHASE       (0)
#define DEFAULT_SPI_BITS        (8)
#define DEFAULT_SPI_FIRSTBIT    (SPI_MSB_FIRST)

#define DEFAULT_SPI0_SCK        (2) 	// SPI0 SCK
#define DEFAULT_SPI0_MOSI       (3)	// SPI0 TX MOSI
#define DEFAULT_SPI0_MISO       (4)	// SPI0 RX MISO

// Probably ESP8285 is connected to SPI1...
#define DEFAULT_SPI1_SCK        (10)	// SPI1 SCK
#define DEFAULT_SPI1_MOSI       (11)	// SPI1 TX MOSI
#define DEFAULT_SPI1_MISO       (8)	// SPI1 RX MISO
#define SPI_CS   9 			// SPI1 CSn - Active LOW

#define SPI_HANDSHARK   21 		// Handshake? ESP32_Ready?

RP2040 Gpio0 is reset

# In https://github.com/IsQianGe/rp2040-spi file mod_wifi_spi.c

//esp8285 power on
mp_hal_pin_output(21); 	// SPI0 CSn - SPI_HANDSHARK? > esp32_ready?

mp_hal_pin_output(22); 	// SPI0 SCK
mp_hal_pin_output(24); 	// SPI1 RX - On pico, this is not exposed in pinout...
mp_hal_pin_output(25);  // SPI1 CSn - Onboard LED on Raspberry Pi pico Board
			
mp_hal_pin_output(SPI_CS); // Pin 9
      
gpio_put(21,1); // On power ON, activate this pins (HIGH)
gpio_put(22,1); // Which one is connected to ESP8285 CHIP_PU Pin?
gpio_put(24,1); 
			
gpio_put(SPI_CS,0); // Active LOW
gpio_put(25,0); // On Power ON, LOW

mp_hal_pin_input(SPI_HANDSHARK); // This pin is checked in order to see if 8285 is ready LOW if ready

gpio_put(SPI_CS,1); // Disable SPI and wait
      
 // esp8285 power down
mp_hal_pin_output(21);	// SPI0 CSn - SPI_HANDSHARK? > esp32_ready?
mp_hal_pin_output(22);	// SPI0 SCK
mp_hal_pin_output(24);	// SPI1 RX - On pico, this is not exposed in pinout...
mp_hal_pin_output(25); 	// SPI1 CSn - Onboard LED on Raspberry Pi pico Board
      
gpio_put(21,0);	// On power OFF, deactivate this pins (LOW)
gpio_put(22,0); // Which one is connected to ESP8285 CHIP_PU Pin?
gpio_put(24,0); // This two GPIOs maybe is custom used on this board...

gpio_put(25,1);  // On power OFF, HIGH

