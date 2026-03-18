# Test Rig GUI Application

Qt Quick used selectively + Widgets to assist test rig ops.

## Filesystem Structure
- `qml`: Qt Quick
- `src`: C++ Sources and Includes

To start building, run this in the root directory of this repo:
```sh
cmake -S . -B build
```
then
```sh
cmake --build build
```
for example. Don't forget to initialize the submodules.
Vcpkg should automatically run due to its definition as the toolchain file in `CMakeLists.txt`.

## Development Resources
- [Qt Documentation](https://doc.qt.io/)
### Visual UI Editor
- [Qt Widgets](https://doc.qt.io/qt-6/qtdesigner-manual.html)
- [QML](https://doc.qt.io/qtcreator/creator-qtquickdesigner-plugin.html)
