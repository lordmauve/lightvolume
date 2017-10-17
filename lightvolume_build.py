"""CFFI build script for lightvolume library."""
import os.path
from cffi import FFI
ffibuilder = FFI()

root = os.path.abspath(os.path.dirname(__file__))


ffibuilder.set_source("_lightvolume",
   r"""
    #include "lightvolume.h"
    """,
    libraries=['GL', 'GLU'],
    sources=['lightvolume.cpp'],
    include_dirs=[root, 'visibility'],
    extra_compile_args=['-std=c++14'],
)


with open('lightvolume.h', 'r') as f:
    hdr = f.read()
ffibuilder.cdef(hdr)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
