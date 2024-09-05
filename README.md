
# ESP32 SPI Bit-Banging Driver

This project demonstrates a custom SPI bit-banging implementation to enable communication between two ESP32 microcontrollers. The driver allows the master ESP32 to send and receive 1000 bytes of data to/from the slave ESP32. The bit-banged SPI protocol provides control over communication without relying on the built-in hardware SPI peripherals.

## Features

- Custom SPI bit-banging implementation.
- Supports data transmission and reception between two ESP32s.
- Handles 1000-byte data transfers in approximately 173 milliseconds.
- Optimized for performance with efficient use of DRAM and IRAM.
- Fully implemented in C using the ESP-IDF framework.

## System Specifications

### Slave ESP32
- **DRAM Usage**: 12,976 bytes (7.2% used)
  - `.data size`: 8,760 bytes
  - `.bss size`: 4,216 bytes
- **IRAM Usage**: 50,902 bytes (38.8% used)
  - `.text size`: 49,875 bytes
  - `.vectors size`: 1,027 bytes
- **Flash Usage**: 116,131 bytes
  - `.text size`: 78,759 bytes
  - `.rodata size`: 37,116 bytes
- **Total Image Size**: 175,793 bytes

### Master ESP32
- **DRAM Usage**: 12,976 bytes (7.2% used)
  - `.data size`: 8,760 bytes
  - `.bss size`: 4,216 bytes
- **IRAM Usage**: 50,902 bytes (38.8% used)
  - `.text size`: 49,875 bytes
  - `.vectors size`: 1,027 bytes
- **Flash Usage**: 116,179 bytes
  - `.text size`: 78,807 bytes
  - `.rodata size`: 37,116 bytes
- **Total Image Size**: 175,841 bytes

## Performance

- **Transfer Speed**: Approximately 173,158 microseconds (173 ms) for 1000 bytes of data transfer.

## Pin Connections

To establish communication between the master and slave ESP32s, connect the following GPIO pins:

| Master Pin | Slave Pin | Function     |
|------------|-----------|--------------|
| GPIO 23    | GPIO 19   | MOSI (Master Out Slave In) |
| GPIO 19    | GPIO 23   | MISO (Master In Slave Out)  |
| GPIO 18    | GPIO 18   | SCK (Clock)  |
| GPIO 5     | GPIO 5    | CS (Chip Select) |

### Wiring Diagram

```
Master ESP32                     Slave ESP32
  GPIO 23  -------------------->  GPIO 19 (MOSI)
  GPIO 19  <--------------------  GPIO 23 (MISO)
  GPIO 18  -------------------->  GPIO 18 (SCK)
  GPIO 5   -------------------->  GPIO 5  (CS)
```

## Setup Instructions

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/ESP32_SPI_BitBang.git](https://github.com/Joel-Mendez0/SPI-Bit-Banging-ESP32.git
   cd SPI-Bit-Banging-ESP32
   ```

2. **Configure the ESP-IDF environment**:
   Follow the official [ESP-IDF installation guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).

3. **Build and flash the project**:
   For both master and slave ESP32s, adjust the project settings (if needed) and run the following commands:
   ```bash
   idf.py set-target esp32
   idf.py build
   idf.py flash
   ```

4. **Monitor the output**:
   ```bash
   idf.py monitor
   ```

5. **Connect the ESP32 boards**:
   Wire the boards as per the pin connections mentioned above.

## How It Works

- **Master** sends 1000 bytes of data to the **Slave**.
- **Slave** receives the data and responds with its own 1000 bytes.
- This communication is achieved through bit-banged SPI, which manually toggles the clock, data, and chip select lines.

## Future Improvements

- Implement error detection and correction mechanisms.
- Optimize the bit-banging speed to further reduce transfer time.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
