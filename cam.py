#! /usr/bin/env python3
import os
import sys
sys.path.insert(1, '~/tetra3')
import tetra3
import socket
#from PIL import image

# send coordinates to lyn
# not the image
print("creating socket...")
socket_path = '/home/user/lyn/image_q'
s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
s.connect(socket_path)
print("connected to lyn!")

print("creating tetra3 object...")
t3 = Tetra3('default_database')

print("hi sir")

