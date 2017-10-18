from setuptools import setup


setup(
    name='lightvolume',
    version='0.1.1',
    author='Daniel Pope',
    author_email='mauve@mauveweb.co.uk',
    description="Light volume calculation and rendering with OpenGL",
    long_description=open('README.rst').read(),
    url='https://github.com/lordmauve/lightvolume',
    py_modules=['lightvolume'],
    install_requires=[
        'cffi>=1.11',
    ],
    setup_requires=['cffi>=1.11'],
    cffi_modules=["lightvolume_build.py:ffibuilder"],
)
