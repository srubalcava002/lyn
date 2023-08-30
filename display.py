#! /usr/bin/env python3
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

from time import sleep

# used to get current positioning for querying nearby objects
import positioning

WIDTH = 128
HEIGHT = 64
CURSOR_SIZE = 3

# draw clear display
image = image.new('1', (width, height))
draw = ImageDraw.Draw(image)
draw.rectangle((0, 0, WIDTH, HEIGHT), outline=0, fill=0)

# draw the cursor in the correct positioning
def draw_cursor_cross(cal_x, cal_y):
    center_x = WIDTH/2 + cal_x
    center_y = HEIGHT/2 + cal_y

    draw.line([(center_x - CURSOR_SIZE, center_y), (center_x + CURSOR_SIZE, center_y)], fill=255, width=0)
    draw.line([(center_x, center_y - CURSOR_SIZE), (center_x, center_y + CURSOR_SIZE)], fill=255, width=0)

# draw the cursor in the correct positioning
# but as an x
def draw_cursor_x(cal_x, cal_y):
    center_x = WIDTH/2 + cal_x
    center_y = HEIGHT/2 + cal_y

    draw.line([(center_x - CURSOR_SIZE, center_y - CURSOR_SIZE), (center_x + CURSOR_SIZE, center_y + CURSOR SIZE)], fill=255, width=0)
    draw.line([(center_x + CURSOR_SIZE, center_y - CURSOR_SIZE), (center_x - CURSOR_SIZE, center_y + CURSOR_SIZE)], fill=255, width=0)

# ! unimplemented !
def draw_local_map():
    # get the coordinates of where the cursor is pointing
    heading = positioning.get_heading()

    current_x = heading[0]
    current_y = heading[1]

    nearby = query_nearby(current_x, current_y)

    return False

# return a list of nearby objects based on 
# current view through sight
def query_nearby(alt, az):
    # how many degrees can you see through the sight?
    # use to get nearby objects

    # how far from reticle to search (radius)
    # guesstimation is telling me that you can see about
    # half a degree in any direction from the reticle...
    # maybe start a local catalog of messier objects
    THRESHOLD = 0.5

    output = []

    view_limit_x = 0
    view_limit_y = 0

    return output

def init_display():
    disp = Adafruit_SSD1306.SSD1306_128_64(rst=24)

    disp.begin()
    disp.clear()
    disp.display()

    # probably redundant
    disp.image(image)

    splash_screen = ImageDraw.Image(image)
    splash_screen.text((0, 0), "* LYN * (0.0.1) ^_^", fill=255)

    disp.image(image)
    disp.display()

    sleep(5)

# dev
def display_test():
    init_display()

    while True:
        for i in range(0, width):
            for j in range(0, height):
                draw_cursor_cross(i, j)
                sleep(1)

if __name__ == '__main__':
    display_test()
