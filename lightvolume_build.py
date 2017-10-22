"""CFFI build script for lightvolume library."""
from __future__ import print_function
import sys
import os.path
from cffi import FFI
ffibuilder = FFI()

root = os.path.abspath(os.path.dirname(__file__))
visibility = os.path.join(root, 'vendor', 'visibility')

# Use GLEW to load OpenGL extensions on Windows only for now
# Set the USE_GLEW=1 environment variable to force
USE_GLEW = (
    sys.platform == 'win32' or
    os.environ.get('USE_GLEW')
)


if sys.platform == 'win32':
    extra_compile_args = ['/std:c++14']
    libraries = ['opengl32', 'glu32']
    if USE_GLEW:
        extra_compile_args += ['/DUSE_GLEW']
        libraries += ['glew32']
else:
    extra_compile_args = ['-std=c++14']
    libraries = ['GL', 'GLU']
    if USE_GLEW:
        extra_compile_args += ['-DUSE_GLEW']
        libraries += ['GLEW']


ffibuilder.set_source(
    "_lightvolume",
    r"""
    #include "lightvolume.h"
    """,
    libraries=libraries,
    sources=['lightvolume.cpp'],
    include_dirs=[root, visibility],
    extra_compile_args=extra_compile_args,
)


with open('lightvolume.h', 'r') as f:
    hdr = f.read()
ffibuilder.cdef(hdr)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
