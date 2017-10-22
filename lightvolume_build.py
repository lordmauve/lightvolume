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

include_dirs = [root, visibility]
library_dirs = []

if sys.platform == 'win32':
    IS_64BIT = sys.maxsize > 2 ** 32

    extra_compile_args = ['/std:c++14']
    libraries = ['opengl32', 'glu32']
    if USE_GLEW:
        extra_compile_args += ['/DUSE_GLEW']
        libraries += ['glew32']

        glew_path = os.path.join(root, 'vendor', 'glew-2.1.0')
        include_dirs += [
            os.path.join(glew_path, 'include')
        ]
        library_dirs += [
            os.path.join(
                glew_path, 'lib', 'Release',
                'x64' if IS_64BIT else 'Win32'
            )
        ]
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
    include_dirs=include_dirs,
    library_dirs=library_dirs,
    extra_compile_args=extra_compile_args,
)


with open('lightvolume.h', 'r') as f:
    hdr = f.read()
ffibuilder.cdef(hdr)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
