from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

from pathlib import Path
long_description = Path('/home/sdoxl/programming/projects/udp_client/README.md').read_text()

c_ext = Extension("udp_client", sources=["_udp_client.c", "udp_client.c"])

setup(
    name='networking_udp_client',
    version='0.3',
    description='Extension providing a basic udp client for making connections, receiving and sending packets in C.',
    ext_modules=[c_ext],
    long_description=long_description,
    long_description_content_type='text/markdown',
    author='lstuma',
    author_email='g.lstuma@gmail.com',
    url='https://github.com/lstuma/udp_client/',
)