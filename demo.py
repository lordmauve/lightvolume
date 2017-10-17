import pyglet
from itertools import product
from pyglet.gl import *

from lightvolume import draw_light, rect

window = pyglet.window.Window(500, 500)


light = 60, 80


OBJECTS = [
    rect(0, 500, 0, 500),
    rect(300, 400, 300, 350),
    rect(60, 70, 20, 30),
    rect(100, 120, 20, 30),
]


@window.event
def on_mouse_motion(x, y, *_):
    global light
    light = (x, y)


@window.event
def on_draw():
    window.clear()
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0)
    draw_light(light, OBJECTS)


pyglet.app.run()
