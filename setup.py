from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

package_name = "homework"

ext_modules = [
    Pybind11Extension(package_name, [
        "src/main.cpp",
    ],
        cxx_std=11
    ),
]

setup(
    name=package_name,
    version='0.4.2',
    ext_modules=ext_modules,
    # extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.9",
)
