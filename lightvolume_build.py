"""CFFI build script for lightvolume library."""
from __future__ import print_function
import sys
import os.path
from cffi import FFI
ffibuilder = FFI()

root = os.path.abspath(os.path.dirname(__file__))
visibility = os.path.join(root, 'visibility')

if not os.path.isdir(visibility):
    sys.exit(
        "The 'visibility' Git subrepository is not present. "
        "Try cloning from https://github.com/trylock/visibility/"
    )
else:
    print('Files present:')
    for path, dirs, files in os.walk(visibility):
        print(path + '/')
        for f in files:
            print(os.path.join(path, f))


ffibuilder.set_source("_lightvolume",
   r"""
    #include "lightvolume.h"
    """,
    libraries=['GL', 'GLU'],
    sources=['lightvolume.cpp'],
    include_dirs=[root, visibility],
    extra_compile_args=['-std=c++14'],
)


with open('lightvolume.h', 'r') as f:
    hdr = f.read()
ffibuilder.cdef(hdr)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
