#define MICROPY_HW_BOARD_NAME "Seeed Wio RP2040"
#define MICROPY_HW_MCU_NAME "rp2040"

#define DEFAULT_UART_BUS_TX   (&pin_GPIO12) // Here we need to change?
#define DEFAULT_UART_BUS_RX   (&pin_GPIO13)
#define DEFAULT_I2C_BUS_SDA   (&pin_GPIO0)
#define DEFAULT_I2C_BUS_SCL   (&pin_GPIO1)
#define DEFAULT_SPI_BUS_SCK   (&pin_GPIO18)
#define DEFAULT_SPI_BUS_MOSI  (&pin_GPIO19)
#define DEFAULT_SPI_BUS_MISO  (&pin_GPIO16)
