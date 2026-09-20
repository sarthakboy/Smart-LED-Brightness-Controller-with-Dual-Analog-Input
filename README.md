# Smart LED Brightness Controller with Dual Analog Input

An Arduino Uno based embedded system that controls LED brightness using analog input and allows the user to switch between two input sources using a push button.

The project demonstrates **ADC reading, PWM-based LED control, GPIO button handling, I²C LCD display, UART diagnostics, and non-blocking timing using `millis()`**.

## Simulation

🔗 **Simulation:** https://velxio.dev/pandeysarthak06/1-smart-led-thermal-protection-brightness-controller/

---

## Project Overview

This project uses an Arduino Uno to control an LED's brightness based on an analog input.

Two analog inputs are available:

- **A0** – Analog input source 1
- **A1** – Analog input source 2

A push button switches between the two input sources.

The selected ADC value is converted from the Arduino's **10-bit ADC range (0–1023)** to an **8-bit PWM range (0–255)** and used to control the LED brightness.

The current mode and LED brightness are displayed on a **16×2 I²C LCD**, while diagnostic information is sent through the **Serial Monitor**.

---

## Features

- Arduino Uno based embedded control system
- Two selectable analog input sources
- Push-button mode switching
- ADC-based LED brightness control
- PWM output for LED brightness
- 16×2 I²C LCD for system status
- UART/Serial diagnostics
- Non-blocking periodic updates using `millis()`
- Percentage-based LED brightness calculation
- Uses `INPUT_PULLUP` for reliable button input

---

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main microcontroller |
| LED | PWM-controlled output |
| Push Button | Switches between A0 and A1 |
| Potentiometer / Analog Source | Analog input |
| 16×2 I²C LCD | Displays mode and brightness |
| Buzzer | Available for future fault indication |
| Resistor | LED current limiting |
| Jumper Wires | Connections |

---

## Pin Configuration

| Arduino Pin | Component | Function |
|---|---|---|
| A0 | Analog Input 1 | Input source 1 |
| A1 | Analog Input 2 | Input source 2 |
| D2 | Push Button | Mode selection |
| D3 | Buzzer | Buzzer output |
| D11 | LED | PWM output |
| A4 | I²C LCD SDA | I²C data |
| A5 | I²C LCD SCL | I²C clock |

---

## Working Principle

The system follows this basic control flow:

```text
Analog Input
     ↓
  ADC Read
     ↓
Select A0 / A1
     ↓
ADC Value (0–1023)
     ↓
Convert to PWM (0–255)
     ↓
  PWM Output
     ↓
   LED Brightness
```

The push button selects which analog input is used.

### Mode Selection

- **Mode A0:** LED brightness is controlled using the value read from A0.
- **Mode A1:** LED brightness is controlled using the value read from A1.

The button uses `INPUT_PULLUP`, so pressing the button produces a **HIGH → LOW transition**.

---

## ADC to PWM Conversion

The Arduino Uno has a **10-bit ADC**, producing values from:

```text
0 → 1023
```

The `analogWrite()` PWM output uses an **8-bit value**:

```text
0 → 255
```

Therefore, the ADC value is converted using:

```cpp
int pwmValue = (reading * 255L) / 1023;
```

The PWM value is then converted into a percentage:

```cpp
int brightnessPercent = (pwmValue * 100L) / 255;
```

Finally, the PWM signal controls the LED:

```cpp
analogWrite(LED, pwmValue);
```

---

## LCD Output

The LCD displays the currently selected input mode and LED brightness.

Example:

```text
MODE: A0
LED B: 75
```

---

## Serial Monitor

The system also sends diagnostic information through UART/Serial at **9600 baud**.

Example:

```text
Mode: A0 | ADC: 512 | LED_B: 50%/100%
```

When the button changes the mode:

```text
Mode changed to: A1
```

This provides basic runtime monitoring and debugging information.

---

## Timing

The project uses Arduino's `millis()` function instead of `delay()` for periodic updates.

The brightness and display information is updated every **1 second**:

```cpp
const unsigned long interval = 1000;
```

This allows the main loop to continuously monitor the button without blocking the program.

---

## Embedded Concepts Demonstrated

- Digital GPIO
- `INPUT_PULLUP`
- ADC / Analog Input
- PWM
- Button edge detection
- I²C communication
- UART / Serial communication
- `millis()` based non-blocking timing
- ADC-to-PWM scaling
- Boolean state management
- Embedded control flow

---

## Software

- **Arduino IDE**
- **Wokwi** – Circuit simulation and testing
- **C/C++** – Arduino firmware

---

## Project Structure

```text
Smart-LED-Brightness-Controller/
│
├── sketch.ino
└── README.md
```

---

## Future Improvements

Possible extensions for this project include:

- Add NTC temperature sensing
- Implement automatic thermal protection
- Add buzzer-based fault warnings
- Display temperature and system status on LCD
- Add AUTO / MANUAL control modes
- Add UART command interface
- Store configuration using EEPROM
- Add sensor filtering and fault detection

---

## Author

**Sarthak Pandey**

Embedded Software / Firmware Engineer  
Embedded C | STM32 | Arduino Uno | ARM Cortex-M

---

## Key Learning

This project helped strengthen practical understanding of **ADC, PWM, GPIO, button state detection, I²C LCD interfacing, UART debugging, and non-blocking embedded programming** using Arduino Uno.
