# SPDX-FileCopyrightText: 2018 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""CircuitPython Essentials NeoPixel example"""
import time
import board
from rainbowio import colorwheel
import neopixel

class NeoPixelRange:
    def __init__(self, neopixel_obj, start, end):
        self._neopixel_obj = neopixel_obj
        self.start = start
        self.end = end
    def fill(self, color):
        for i in range(self.start, self.end):
            self._neopixel_obj[i] = color
    def show(self):
        self._neopixel_obj.show()
    def __len__(self):
        return (self.end - self.start)
    def __setitem__(self, key, color):
        self._neopixel_obj[self.start+key] = color

PIN = board.D1
NUM_PIXELS = 23

PIXELS = neopixel.NeoPixel(PIN, NUM_PIXELS, brightness=0.03, auto_write=False)
OUTER_RING = NeoPixelRange(PIXELS, 0, 16)
INNER_RING = NeoPixelRange(PIXELS, 17, 23)
CENTER = NeoPixelRange(PIXELS, 16, 17)

RED = (255, 0, 0)
YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
OFF = (0, 0, 0, 0)

outer_active = 0
inner_active = 0

while True:
    for i in range(len(OUTER_RING)):
        if i == outer_active:
            OUTER_RING[i] = CYAN
        else:
            OUTER_RING[i] = OFF
    
    outer_active = (outer_active + 1) % len(OUTER_RING)
        
    for i in range(len(INNER_RING)):
        if i == inner_active:
            INNER_RING[i] = PURPLE
        else:
            INNER_RING[i] = OFF
    
    if outer_active == 7:
        CENTER[0] = BLUE
    if outer_active == 15:
        CENTER[0] = OFF

    inner_active = (inner_active + 1) % len(INNER_RING)
    
    PIXELS.show()
    time.sleep(0.01)
