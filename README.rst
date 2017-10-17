lightvolume
===========

This package provides the module ``lightvolume``, which offers a CFFI binding
to `trylock/visibility`_. This, in turn, is a C++ implementation of `the
visibility algorithm`_ documented in detail (with awesome interactive demos)
on the Red Blob Games website.


.. _`trylock/visibility`: https://github.com/trylock/visibility
.. _`the visibility algorithm`: http://www.redblobgames.com/articles/visibility/


API
---

First, import ``lightvolume``::

    import lightvolume

Then, we can create a number of shadow-casting bodies::

    objects = [
        lightvolume.rect(0, 0, 500, 500),  # outer bounds - this is needed
        lightvolume.rect(20, 30, 10, 20),
        lightvolume.rect(290, 300, 100, 300),
    ]


Finally, we can render the lit area cast by a light in this scene (an OpenGL
context must already have been created and appropriate GL state set)::

    light = 90, 200
    lightvolume.draw_light(light, objects)


This module is intended to be used with appropriate shaders to provide
attenuation, surface interactions such as bump mapping, and so on.
