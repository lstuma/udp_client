from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

c_ext = Extension("udp_client", sources=["_udp_client.c", "udp_client.c"])

setup(
    name='networking_udp_client',
    version='0.2',
    description='Extension providing a basic udp client for making connections, receiving and sending packets in C.',
    ext_modules=[c_ext]
)