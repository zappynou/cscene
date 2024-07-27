# CScene

## Project

### What ?

CScene (litt. "C Scene [library]") is a library which provides a widget (=the "scene") where an application can draw onto.

### Why ?

It is meant for other side-projects to not bother re-inventing the wheel, when all you want is "to draw something and move around".

### How ?

The CScene library provides the basic signals and events handling, for you to focus on the actual content: events and drawing.

#### The mouse events

The scene widget handles the basic mouse events, such as:

- `move`, the offsets of the scene move around by clicking and dragging the mouse;
- `scale`, the ratio of the scene scale increases/decreases with the mouse wheel;
- `click`, this signal allows the application to detect when a mouse button is clicked;

#### The rendering events

The scene widget also provides rendering events, such as:

- `draw`, at anytime the application can redraw the scene as needed;

## Build instructions

The only supported build system is autoconf/automake.
It is only tested on GNU/Linux and MacOS (aarch64), more architectures and systems are welcome too (feel free to pull-request).

The build procedure is follows:

~~~
$ autoreconf -fi
$ ./configure [--enable-debug]
$ make
~~~
