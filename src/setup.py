from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

c_ext = Extension("tcp_client", sources=["_tcp_client.c", "tcp_client.c"])

setup(
    name='networking_tcp_client',
    version='0.2',
    description='Extension providing a basic tcp client for making connections, receiving and sending packets in C.',
    ext_modules=[c_ext]
)