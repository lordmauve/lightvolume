import pyglet
from itertools import product
from pyglet.gl import *

from _lightvolume import lib, ffi

window = pyglet.window.Window(500, 500)


light = 60, 80


def rect(l, r, b, t):
    return [
        l, b,
        r, b,
        r, b,
        r, t,
        r, t,
        l, t,
        l, t,
        l, b
    ]


SEGMENTS = [
    *rect(0, 500, 0, 500),
    *rect(300, 400, 300, 350),
    *rect(60, 70, 20, 30),
    *rect(100, 120, 20, 30),
]


lib.init()


@window.event
def on_mouse_motion(x, y, *_):
    global light
    light = (x, y)


@window.event
def on_draw():
    window.clear()
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 0.0)
    glDisable(GL_CULL_FACE)
    light_x, light_y = light

    segments = ffi.new('float []', SEGMENTS)

    lib.draw_visibility(light_x, light_y, segments, len(segments))


pyglet.app.run()
