Willdox - Will's custom REDOX keyboard
======

## Note
lufa.c file overrides tmk_core/protocol/lufa/lufa.c, adding a 2500ms delay before initialize main, for qmk to load after the initialization of the oled screens I've added in the keyboard.


## First Time Setup

Download or clone the `qmk_firmware` repo and navigate to its top level directory. Clone this repo inside the keyboards folder and once your build environment is setup, you'll be able to generate the default .hex using:

```
$ make willdox:default
```

You will see a lot of output and if everything worked correctly you will see the built hex file:

```
willdox_default.hex
```

Required Hardware
-----------------

Apart from diodes and key switches for the keyboard matrix in each half, you
will need:

* 2 Arduino Pro Micros. You can find these on AliExpress.
* 2 TRRS sockets and 1 TRRS cable, or 2 TRS sockets and 1 TRS cable. Worth notice that the PCB is made for serial communication, so only three wires are necessary to connect both halves.
* 2 I2C OLED screens. You can find these on AliExpress too.
* Materials and tools to make the PCB (in my case, I used phenolite boards and ferric chloride, the board lines are thick ehough for that),

Notes on Software Configuration
-------------------------------

Configuring the firmware is similar to any other QMK project. One thing
to note is that `MATRIX_ROWS` in `config.h` is the total number of rows between
the two halves, i.e. if your split keyboard has 4 rows in each half, then use
`MATRIX_ROWS=8`.

Also, the current implementation assumes a maximum of 8 columns, but it would
not be very difficult to adapt it to support more if required.

Flashing
-------
From the top level `qmk_firmware` directory run `make KEYBOARD:KEYMAP:avrdude` for automatic serial port resolution and flashing.
Example: `make lets_split/rev2:default:avrdude`


Choosing which board to plug the USB cable into (choosing Master)
--------
Because the two boards are identical, the firmware has logic to differentiate the left and right board.

It uses two strategies to figure things out: looking at the EEPROM (memory on the chip) or looking if the current board has the usb cable.

The EEPROM approach requires additional setup (flashing the eeprom) but allows you to swap the usb cable to either side.

The USB cable approach is easier to setup and if you just want the usb cable on the left board, you do not need to do anything extra.

### Setting the left hand as master
If you always plug the usb cable into the left board, nothing extra is needed as this is the default. Comment out `EE_HANDS` and comment out `I2C_MASTER_RIGHT` or `MASTER_RIGHT` if for some reason it was set.

### Setting the right hand as master
If you always plug the usb cable into the right board, add an extra flag to your `config.h`
```
 #define MASTER_RIGHT
```

### Setting EE_hands to use either hands as master
If you define `EE_HANDS` in your `config.h`, you will need to set the
EEPROM for the left and right halves.

The EEPROM is used to store whether the
half is left handed or right handed. This makes it so that the same firmware
file will run on both hands instead of having to flash left and right handed
versions of the firmware to each half. To flash the EEPROM file for the left
half run:
```
avrdude -p atmega32u4 -P $(COM_PORT) -c avr109 -U eeprom:w:"./quantum/split_common/eeprom-lefthand.eep"
// or the equivalent in dfu-programmer

```
and similarly for right half
```
avrdude -p atmega32u4 -P $(COM_PORT) -c avr109 -U eeprom:w:"./quantum/split_common/eeprom-righthand.eep"
// or the equivalent in dfu-programmer
```

NOTE: replace `$(COM_PORT)` with the port of your device (e.g. `/dev/ttyACM0`)

After you have flashed the EEPROM, you then need to set `EE_HANDS` in your config.h, rebuild the hex files and reflash.

Note that you need to program both halves, but you have the option of using
different keymaps for each half. You could program the left half with a QWERTY
layout and the right half with a Colemak layout using bootmagic's default layout option.
Then if you connect the left half to a computer by USB the keyboard will use QWERTY and Colemak when the
right half is connected.


Notes on Using Pro Micro 3.3V
-----------------------------

Do update the `F_CPU` parameter in `rules.mk` to `8000000` which reflects
the frequency on the 3.3V board.

Also, if the slave board is producing weird characters in certain columns,
update the following line in `matrix.c` to the following:

```
// _delay_us(30);  // without this wait read unstable value.
_delay_us(300);  // without this wait read unstable value.
```
