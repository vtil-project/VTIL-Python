#! /usr/bin/python3
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from setuptools.command.install_lib import install_lib
from distutils.command.build import build
from distutils.command.sdist import sdist
from distutils.dir_util import copy_tree
import platform
import sys
import os


VERSION = '0.0.3'
CORE_COMMIT = 'c13dbc0'
PYBIND11_COMMIT = 'd54d6d8'


class CMakeExtension(Extension):
    def __init__(self, name, src_dir, additional=None, sources=None):
        if not sources:
            sources = []
            for dir_path, _, files in os.walk(src_dir):
                for file_name in files:
                    sources.append(os.path.join(dir_path, file_name))
            if additional:
                sources.extend(additional)

        super().__init__(name=name, sources=sources)


class InstallCMakeLibs(install_lib):
    def run(self):
        self.skip_build = os.path.exists('build/vtil.pyd')
        super().run()


class BuildVTIL(build):
    def run(self):
        self.run_command("build_ext")
        super().run()


class PackageVTIL(sdist):
    def run(self):
        # Packaging VTIL doesn't require the build sources.
        self.distribution.package_data = {}
        self.distribution.packages = []
        super().run()


class BuildCMakeExtension(build_ext):
    def run(self):
        for extension in self.extensions:
            if extension.name == 'VTIL':
                self.build()

    def build(self):
        import git

        # Remove old build
        if not os.path.exists('build/vtil.pyd'):
            os.makedirs('build/lib', exist_ok=True)

            # Update submodules
            self.announce('Updating submodules ..')
            if os.path.exists('.git'):
                # We are running from a cloned version
                git.Repo('.').submodule_update(init=True, recursive=False)
            else:
                # We are running from a pypi tar.gz version
                if not os.path.exists('external/core'):
                    git.Repo.clone_from('https://github.com/vtil-project/VTIL-Core.git', 'external/core').git.checkout(CORE_COMMIT)
                if not os.path.exists('external/pybind11'):
                    git.Repo.clone_from('https://github.com/pybind/pybind11.git', 'external/pybind11').git.checkout(PYBIND11_COMMIT)

            self.announce('Preparing build for platform ..', level=3)
            self.spawn(self.build_for_platform())

            self.announce('Building ..', level=3)
            self.spawn(self.build_cmake())

        self.announce('Generating libs ..', level=3)
        self.spawn(self.gen_libs())

        self.announce('Copying wrappers ..', level=3)
        copy_tree("src/wrappers", "vtil")

    @staticmethod
    def build_for_platform():
        extras = []
        if platform.system() == 'Windows':
            import cmakegenerators

            if 'Visual Studio 16 2019' not in [gen.name for gen in cmakegenerators.get_generators()]:
                raise Exception('Visual Studio 2019 not found')
            
            extras = ['-G', 'Visual Studio 16 2019']

        return \
            [
                'cmake',
                '-DPYTHON_EXECUTABLE=' + sys.executable,
                '-DVTIL_PYTHON_VERSION=' + VERSION,
                '-S', '.',
                '-B', 'build'
            ] + extras

    @staticmethod
    def build_cmake():
        return \
            [
                'cmake',
                '--build', 'build',
                '--config', 'Release'
            ]

    @staticmethod
    def gen_libs():
        return \
            [
                "cmake",
                "--install", "build",
                "--component", "pyd",
                "--prefix", "vtil"
            ]


setup(
    name='VTIL',
    version=VERSION,
    author='Daniel. (@L33T)',
    description='Virtual-machine Translation Intermediate Language',
    long_description='VTIL Project, standing for Virtual-machine Translation Intermediate Language, is a set of tools'
                     ' designed around an optimizing compiler to be used for binary de-obfuscation and'
                     ' de-virtualization.\n\nThe main difference between VTIL and other optimizing compilers such as '
                     'LLVM is that it has an extremely versatile IL that makes it trivial to lift from any'
                     ' architecture including stack machines. Since it is built for translation, VTIL does not abstract'
                     ' away the native ISA and keeps the concept of the stack, physical registers, and the non-SSA'
                     ' architecture of a general-purpose CPU as is. Native instructions can be emitted in the middle '
                     'of the IL stream and the physical registers can be addressed from VTIL instructions freely.\n\n'
                     'VTIL also makes it trivial to emit code back into the native format at any virtual address'
                     ' requested without being constrained to a specific file format.',
    url='https://github.com/vtil-project/VTIL-Python',
    classifiers=[
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Development Status :: 3 - Alpha',
        'Natural Language :: English',
        'Operating System :: MacOS',
        'Operating System :: POSIX :: Linux',
        'Operating System :: Microsoft :: Windows',
        'Programming Language :: C++',
        'Topic :: Education'
    ],
    python_requires='>=3.4',
    license='BSD 3-Clause "New" or "Revised" License',
    cmdclass={
        'sdist': PackageVTIL,
        'build': BuildVTIL,
        'build_ext': BuildCMakeExtension,
        'install_lib': InstallCMakeLibs
    },
    setup_requires=['cmake>=3.15', 'cmake-generators', 'GitPython', 'future_fstrings'],
    install_requires=['pybind11'],
    ext_modules=[CMakeExtension('VTIL', src_dir='src', additional=['LICENSE.md', 'CMakeLists.txt'])],
    keywords='VTIL, VTIL Project, vtil, Virtual-machine Translation Intermediate Language, '
             'Translation Intermediate Language, Intermediate Language',
    zip_safe=True,
    packages=['vtil'],
    package_data={
        'vtil': ['vtil.pyd', 'vtil.so', '*.py', '**/*.py'],
    }
)
