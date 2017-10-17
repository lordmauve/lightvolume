from cffi import FFI
ffibuilder = FFI()


ffibuilder.set_source("_lightvolume",
   r"""
    #include "lightvolume.h"
    """,
    libraries=['GL', 'GLU'],
    sources=['lightvolume.cpp'],
    include_dirs=['visibility'],
    extra_compile_args=['-std=c++14'],
)   # or a list of libraries to link with
    # (more arguments like setup.py's Extension class:
    # include_dirs=[..], extra_objects=[..], and so on)


with open('lightvolume.h', 'r') as f:
    hdr = f.read()
ffibuilder.cdef(hdr)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
