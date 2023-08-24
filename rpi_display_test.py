#! /usr/bin/env python3
import time

import Adafruit_SSD1306

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

width = 128
height = 64

disp = Adafruit_SSD1306.SSD1306_128_64(rst=24)

disp.begin()
disp.clear()
disp.display()

image = Image.new('1', (width, height))
draw = ImageDraw.Draw(image)
draw.rectangle((0,0,width,height), outline=0, fill=0)

image.putpixel((64,32), 255)

disp.image(image)
disp.display()

