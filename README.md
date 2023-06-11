# Tetris on Arduino ![GitHub issues](https://img.shields.io/github/issues/a-regular-pear/arduino-tetris) ![GitHub](https://img.shields.io/github/license/a-regular-pear/arduino-tetris) 
A port of the popular videogame Tetris on an arduino Uno

## Components needed
- 1 - Arduino Uno Rev3

- 1 - SPI LCD Display using the ILI9341 driver

- 7 - 2.2KOhm resistors 

- 7 - 4.7KOhm resistors

- 4 - 10KOhm resistors

- 4 - Push buttons

### A simple schematic of the project
![A schematic of the project](/schematic/schematic.png)

## Software needed
The project relies on
- [SPI Library for arduino](https://www.arduino.cc/reference/en/language/functions/communication/spi/)
- [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit ILI9341 Library](https://github.com/adafruit/Adafruit_ILI9341)

## Contribute
1. Create a fork of the project
2. Create a branch for the feature you want to implement (`git checkout -b feature`)
3. Stage (`git add .`) and commit (`git commit -m "feature"`)
4. Push to branch (`git push origin feature`)
5. Create a pull request
