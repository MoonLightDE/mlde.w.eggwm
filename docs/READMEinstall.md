mlde : eggwm
============

A minimalist QT window manager for QT framework technology

This its a minimal implementation for a defult window manager into Moonlight Desktop.

![mlde-eggwm-qt5.png](mlde-eggwm-qt5.png)

## Requirements

Requirements and QT5 framework installed with qmake and development headers, for test Xephyr are good choice:

* GCC >> 4.0
* QT
  * Qt >> 5.2
  * Qt >> 4.5
* Xephyr

## Build

### Build using qt4

```
export QT_SELECT=4
qmake -makefile
make
make install
```

### Build using qt5

```
export QT_SELECT=5
qmake -makefile
make
make install
```

## Install to system

### Testing without exit session

Firs get a working display test with Xephyr, in a console shell lauch:

```
$ Xephyr :1 -ac -screen 900x700 &
```

Then due eggwm lacks of replace-ment function lauch to that display:

```
$ eggwm -display :1
```

Now lauch applications that can be specified what display to use, as `Xterm`, and from that lauch other apps:

```
$ xterm -display :1
```
