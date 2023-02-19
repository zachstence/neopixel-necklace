# SPDX-FileCopyrightText: 2018 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""CircuitPython Essentials NeoPixel example"""
import time
import board
from rainbowio import colorwheel
import neopixel

PIN = board.D1
NUM_PIXELS = 23

pixels = neopixel.NeoPixel(PIN, NUM_PIXELS, brightness=0.03, auto_write=False)

RED = (255, 0, 0)
YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
OFF = (0, 0, 0, 0)

active = 0

while True:
    for i in range(NUM_PIXELS):
        if i == active:
            pixels[i] = CYAN
        else:
            pixels[i] = OFF
    
    pixels.show()
    active = (active + 1) % NUM_PIXELS
    time.sleep(0.01)
