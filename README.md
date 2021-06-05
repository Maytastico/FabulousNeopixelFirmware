# FabulousNeopixelFirmware
This lets you control your leds with a infrared remote, a Arduino and a infrared receiver, either a fancy animation or a simple static color. I ever wanted a simple firmware to control my neopixel lights so I programmed it myself. It is based on the Adafruit Neopixel library and can be extended for your needs.

# How build

[Prototyping Board Design](https://github.com/MacaroniDamage/FabulousNeopixelFirmware/blob/main/FabolousNeopixelFirmware_Steckplatine.png)

[PCB Design](https://github.com/MacaroniDamage/FabulousNeopixelFirmware/blob/main/FabolousNeopixelFirmware_Schaltplan.png)

You need:

1. Addressable LED stripes either ws2812b or sk6812 
2. 5 V Power Source
3. Infrared Receiver
4. Electrolyt Condensator e.q 220 nF
5. Resistor with at least 470Ohm
6. Arduino Nano or similar

# How to install

1. You need to install Visual Studio Code
2. Then you will need to install PlatformIO as an extension
3. After that you can specify what infrared remote you have and how many and also what type of leds you want to use.
4. Then you can compile and program your arduino with it.
5. You have a functional Neopixel controler

# Contact

You can contact me on may@jeffsky.de for help
