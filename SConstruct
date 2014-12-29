import os

VariantDir('build', 'src', duplicate=0)

env=Environment(
    CPPPATH='src',
    CXX='clang++',
    CXXFLAGS='-std=c++14 -Wall -Wextra -Werror -O3 -g -march=native -flto',
    LINKFLAGS='-flto',
    SCONS_CXX_STANDARD="c++14",
    ENV={'TERM': os.environ['TERM']},
    variant_dir='build'
)

paths = [
    'build/linear/*.cpp',
    'build/tracer/images/*.cpp',
    'build/tracer/light/*.cpp',
    'build/tracer/items/geometry/*.cpp',
    'build/tracer/items/materials/*.cpp',
    'build/tracer/items/*.cpp',
    'build/tracer/scene/*.cpp',
    'build/tracer/parsers/*.cpp',
    'build/tracer/*.cpp',
]

sources = [g for p in paths for g in Glob(p)]

env.Program('build/main', sources, )
