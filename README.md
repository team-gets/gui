# Test Rig GUI Application

Qt Quick used selectively + Widgets to assist test rig ops.

## Filesystem Structure
- `qml`: Qt Quick
- `src`: C++ Sources and Includes

## Build Guide
To start building,
you must have binaries or the source of Qt of at least version 6.10.0.
This is a complicated process.
Using official sources from [qt.io](https://qt.io/)
or an unofficial tool like [`aqtinstall`](https://aqtinstall.readthedocs.io/en/latest/)
should work.

Once you have acquired Qt to at least version 6.10.0,
run this in the root directory of this repo:
```sh
cmake -S . -B build
```
then
```sh
cmake --build build
```
for example. Don't forget to initialize the submodules.
Vcpkg should automatically run due to its definition as the toolchain file in `CMakeLists.txt`.
Additionally, there are several presets for CMake that can be used.
Consider reading `CMakePresets.json` in the root of this repo.

## Development Resources
- [Qt Documentation](https://doc.qt.io/)
### Visual UI Editor
- [Qt Widgets](https://doc.qt.io/qt-6/qtdesigner-manual.html)
- [QML](https://doc.qt.io/qtcreator/creator-qtquickdesigner-plugin.html)
