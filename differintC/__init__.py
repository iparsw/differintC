import os
import sys
import ctypes
from pathlib import Path
import importlib.resources
import warnings


def _load_dll():
    if sys.platform != "win32":
        return

    # Get package directory
    package_dir = Path(__file__).parent

    # 1. Try package directory (where __init__.py is)
    dll_path = package_dir / "libfftw3-3.dll"
    if dll_path.exists():
        os.add_dll_directory(str(package_dir))
        print(f"Loaded FFTW DLL from package directory: {dll_path}")
        return

    # 2. Try site-packages root directory
    site_packages_dll = package_dir.parent / "libfftw3-3.dll"
    if site_packages_dll.exists():
        os.add_dll_directory(str(site_packages_dll.parent))
        print(f"Loaded FFTW DLL from site-packages root: {site_packages_dll}")
        return

    # 3. Try using importlib.resources
    try:
        with importlib.resources.path("differintC", "libfftw3-3.dll") as dll_path:
            if dll_path.exists():
                os.add_dll_directory(str(dll_path.parent))
                print(f"Loaded FFTW DLL via importlib: {dll_path}")
                return
    except Exception as e:
        warnings.warn(f"importlib.resources failed: {e}")

    # 4. Try Windows system directory
    system_dll = Path("C:/Windows/System32") / "libfftw3-3.dll"
    if system_dll.exists():
        os.add_dll_directory(str(system_dll.parent))
        print(f"Loaded FFTW DLL from system directory: {system_dll}")
        return

    # 5. Try loading directly (if in PATH)
    try:
        ctypes.CDLL("libfftw3-3.dll")
        print("Loaded FFTW DLL directly from PATH")
        return
    except OSError:
        pass

    # If all else fails
    raise RuntimeError(
        "FFTW DLL not found! Checked locations:\n"
        + f"1. Package directory: {package_dir}/libfftw3-3.dll\n"
        + f"2. Site-packages root: {package_dir.parent}/libfftw3-3.dll\n"
        + f"3. System directory: C:/Windows/System32/libfftw3-3.dll"
    )


# Load DLL before importing C++ module
try:
    _load_dll()
except RuntimeError as e:
    print(f"FFTW DLL loading failed: {e}")
    # Try to proceed anyway - might be available in PATH
    try:
        ctypes.CDLL("libfftw3-3.dll")
        print("Successfully loaded FFTW DLL after initial failure")
    except OSError:
        raise

# Import the C++ extension
from ._differintC import *  # type: ignore # Directly import from site-packages

# Add version attribute
from ._version import __version__
