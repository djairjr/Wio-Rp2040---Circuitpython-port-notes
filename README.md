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

User in forum informs that Micropython port for this board is same as this version:
https://github.com/IsQianGe/rp2040-spi

# So, i want to check if there is any indication of connections in code...

// Probably ESP8285 is connected to SPI1...
#define DEFAULT_SPI1_SCK        (10)	// SPI1 SCK
#define DEFAULT_SPI1_MOSI       (11)	// SPI1 TX MOSI
#define DEFAULT_SPI1_MISO       (8)	// SPI1 RX MISO
#define SPI_CS   9 			// SPI1 CSn - Active LOW

#define SPI_HANDSHARK   21 		// Handshake? ESP32_Ready?

RP2040 Gpio0 is reset

# In Arduino Hardware and Libraries for this board i've found this:
#define PIN_SPI1_MISO  (8u)
#define PIN_SPI1_MOSI  (11u)
#define PIN_SPI1_SCK   (10u)
#define PIN_SPI1_SS    (9u)

#define NINA_GPIO0 (21u)
#define SPIWIFI_SS (24u)
#define SPIWIFI_ACK (21u)
#define SPIWIFI_RESET (22u)

# From Adafruit_CircuitPython_ESP32SPI library, I need three pins...
esp32_cs 	= DigitalInOut(board.ESP_CS) 	// >> Probably SPI1_SS - GP9 ou GP24
esp32_ready 	= DigitalInOut(board.ESP_BUSY) 	// >> SPIWIFI_ACK      - GP21
esp32_reset 	= DigitalInOut(board.ESP_RESET) // >> SPIWIFI_RESET    - GP22


