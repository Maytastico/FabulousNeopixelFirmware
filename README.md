# FabulousNeopixelFirmware
This lets you control your leds with a infrared remote, a Arduino and a infrared receiver, either a fancy animation or a simple static color. I ever wanted a simple firmware to control my neopixel lights so I programmed it myself. It is based on the [Adafruit Neopixel library](https://github.com/adafruit/Adafruit_NeoPixel) and can be extended for your needs.

# How build

Prototyping Design

![Prototyping Board Design](https://raw.githubusercontent.com/MacaroniDamage/FabulousNeopixelFirmware/main/FabolousNeopixelFirmware_Steckplatine.png)

PCB Design

![PCB Design](https://raw.githubusercontent.com/MacaroniDamage/FabulousNeopixelFirmware/main/FabolousNeopixelFirmware_Schaltplan.png)

You need:

1. Addressable LED stripes either ws2812b or sk6812 
2. 5 V Power Source
3. Infrared Receiver
4. Electrolyt Condensator e.q 220 nF
5. Resistor with at least 470Ohm
6. Arduino Nano or similar

Notice: A condensator as well as a resistor are for good measure to protect the first led on a stripe you don't have to use it, if you work with few Neopixels.



# How to install

1. You need to install Visual Studio Code
2. Then you will need to install PlatformIO as an extension
3. After that you can specify what infrared remote you have and how many and also what type of leds you want to use.
4. Then you can compile and program your arduino with it.
5. You have a functional Neopixel controler

# What kind of Receivers are already supported

I used receivers from commercial LED stripe kits. If yours look like these below, they should probably work with those codes I used.

## Remote with 22 Buttons

![22 Button Remote](https://raw.githubusercontent.com/MacaroniDamage/FabulousNeopixelFirmware/main/22Buttons.jpg)

## Remote with 44 Buttons

![44 Buttons](https://raw.githubusercontent.com/MacaroniDamage/FabulousNeopixelFirmware/main/44Buttons.jpg)

# Contact

You can contact me on may@jeffsky.de for help
