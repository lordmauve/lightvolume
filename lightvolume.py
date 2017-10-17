"""lightvolume Python interface."""

from _lightvolume import lib, ffi

__metaclass__ = type


# Initialise the library (allocate VBO)
lib.init()



class rect:
    """An axis-aligned rectangle."""
    __slots__ = ('l', 'r', 'b', 't')

    def __init__(self, l, r, b, t):
        self.l = l
        self.r = r
        self.b = b
        self.t = t

    def __iter__(self):
        yield self.l
        yield self.r
        yield self.b
        yield self.t

    @property
    def _segments(self):
        l, r, b, t = self
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


def draw_light(light, objects):
    light_x, light_y = light

    segments = ffi.new(
        'float []',
        [coord for obj in objects for coord in obj._segments]
    )
    lib.draw_visibility(light_x, light_y, segments, len(segments))
