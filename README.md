# photo_info_provider
Provider app for photos from unsplash.com API

Installation
1. Clone repo:

```git clone --recurse-submodules ${link_to_repo}```

2. Install any ```compiler``` you want, ```conan```, ```cmake``` in this order. Add theirs binaries directories to ```PATH```.
3. Install ```vcpkg``` (might be deprecated and removed with conan soon, but works fine now):

```cd ${directory_for_vcpkg} ; git clone https://github.com/microsoft/vcpkg ; cd vcpkg ; ./bootstrap-vcpkg.bat ; vcpkg integrate install```

Than do this command:

```./vcpkg.exe install curl:x64-windows```

4. Go to path/to/this/cloned/repo/
5. Prepare build direcory:

```mkdir build ; cd build ; conan install .. ; cd ..```

6. Generate build with cmake:

```cmake -S . -B build -DXARCH_WINDOWS="${XARCH_WINDOWS}" -DPATH_TO_VCPKG="${PATH_TO_VCPKG}"```

Example:

```cmake -S . -B build -DXARCH_WINDOWS="x64-windows" -DPATH_TO_VCPKG='C:\Program Files\vcpkg'```

7. Build sources:

```cmake --build --build```
