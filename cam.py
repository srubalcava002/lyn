#! /usr/bin/env python3
import os
import sys
sys.path.insert(1, '~/tetra3')
import tetra3
import socket

# send coordinates to lyn
# not the image
socket_path = '/home/user/lyn/image_q'
s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
s.connect(socket_path)

print("hi sir")

