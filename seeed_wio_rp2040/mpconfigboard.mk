USB_VID = 0x239a
USB_PID = 0x80f4
USB_PRODUCT = "Seeed Wio RP2040"
USB_MANUFACTURER = "SeeedStudio"

CHIP_VARIANT = RP2040
CHIP_FAMILY = rp2

EXTERNAL_FLASH_DEVICES = "W25Q64JVxQ"

CIRCUITPY__EVE = 1

# Include these Python libraries in firmware.
FROZEN_MPY_DIRS += $(TOP)/frozen/Adafruit_CircuitPython_ESP32SPI
