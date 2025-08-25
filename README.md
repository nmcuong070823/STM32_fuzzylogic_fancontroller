# STM32_fuzzylogic_fancontroller
A prototype system of using fuzzy logic algorithm on STM32 BluePill based on temperature and humidity to control the speed (PWM) of DC Fan

This project was replicated from Ivan Fernandes Alonso's project, which was built using ESP32 Microcontroller. Link to author's project: https://github.com/IFAlonso/fuzzyspeedfancontroller
## Project's main components and wiring diagram
### Main components
* STM32F103C8T6 BluePill Microcontroller
* BME280 Sensor
* RCWL-0516 Radar Sensor
* OLED SSD1306 I2C
* Mosfet PWM Module
* DC Fan - Ventilator
### Wiring diagram
* BME280 - OLED SSD1306 I2C
  * SCL -> PB6
  * SDA -> PB7
* RCWL-0516
   * OUT -> PA1
* Mosfet PWM Module
    * PWM -> PA8
* VCC -> VCC
* GND -> GND
![image alt](https://github.com/nmcuong070823/STM32_fuzzylogic_fancontroller/blob/ab45b46b5cfee8fb5ab32bb0b2944a4ccd6c8c37/Wiring%20diagram.JPG)
