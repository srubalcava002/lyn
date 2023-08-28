#! /usr/bin/env python3
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

# used to get current positioning for querying nearby objects
import positioning

WIDTH = 128
HEIGHT = 64
CURSOR_SIZE = 3

# draw clear display
image_blank = image.new('1', (width, height))
draw = ImageDraw.Draw(image)
draw.rectangel((0, 0, WIDTH, HEIGHT), outline=0, fill=0)

def init_display():
    disp = Adafruit_SSD1306.SSD1306_128_64(rst=24)

    disp.begin()
    disp.clear()
    disp.display()

    disp.image(image)

# draw the cursor in the correct positioning
def draw_cursor(cal_x, cal_y):
    center_x = WIDTH/2 + cal_x
    center_y = HEIGHT/2 + cal_y

    draw.line([(center_x - CURSOR_SIZE, center_y), (center_x + CURSOR_SIZE, center_y)], fill=255, width=0)
    draw.line([(center_x, center_y - CURSOR_SIZE), (center_x, center_y + CURSOR_SIZE)], fill=255, width=0)

# unimplemented
# should probably call anotha function to draw an object based on coordinates
def draw_local_map():


# draw an object 
def draw_object(alt, az):

# return a list of nearby objects based on 
# current view through sight
def query_nearby():
    # how many degrees can you see through the sight?
    # use to get nearby objects
    view_limit_x = 0
    view_limit_y = 0
