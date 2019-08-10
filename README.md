# Dangerous Orbit

2D space shooter. It is a demonstration project of [Quasura](https://github.com/jcoder39/Quasura)

## Dependencies

- C++ 17;
- cmake 3.11;
- SFML(tested on SFML 2.5.1);
- Quasura;

## Building

- ### Binaries
[Windows, Linux](http://spectrobyte.com/DangerousOrbit.html)

- ### Windows.
 using Developer Command Prompt for VS 2017:
```console
git clone https://github.com/jcoder39/Dangerous-Orbit.git
cd DangerousOrbit
git submodule update --init --recursive
git submodule update --remote
```
add #define _HAS_AUTO_PTR_ETC 1 to external\SFML\src\SFML\Audio\AudioDevice.cpp before any includings.
```console
mkdir build
cd build
cmake -DSFML_USE_STATIC_STD_LIBS=TRUE -DBUILD_SHARED_LIBS=FALSE -G "NMake Makefiles" ..
nmake
.\DangerousOrbit
```

- ### Linux:
```console
git clone https://github.com/jcoder39/Dangerous-Orbit.git
cd DangerousOrbit
git submodule update --init --recursive
git submodule update --remote
mkdir build
cd build
cmake ..
make
./DangerousOrbit
```

## Game graphics

[alien](http://millionthvector.blogspot.com/p/free-sprites.html)
[ship](https://opengameart.org/users/skorpio)
[asteroids](https://opengameart.org/users/phaelax)
[explosions](https://29a.ch)

## License

GPL v3. See [COPYING](COPYING) for the GNU GENERAL PUBLIC LICENSE
