from setuptools import setup


setup(
    name='lightvolume',
    version='0.1.3',
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
    classifiers=[
        'Development Status :: 4 - Beta',
        'Topic :: Multimedia :: Graphics',
        'License :: OSI Approved :: BSD License',
        'Intended Audience :: Developers',
        'Operating System :: MacOS :: MacOS X',
        'Operating System :: Microsoft :: Windows',
        'Operating System :: POSIX',
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
    ],
)
