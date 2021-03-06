## Synopsis

Daylight is a simple 3d modeling/viewing software built with Qt, OpenGL, Bullet Physics
This branch is made to automate data generation process for a paper

## Code Example

Will build this late

## Functionalities

__NAVIGATION__
1. Click to select object in the scene and focus on the object
2. Left mouse button drag to rotate the camera around the focus point
3. Middle mouse button drag to pan the camera


__RENDERING__
Rendering sample:
![alt text](https://github.com/Shunxu-H/DayLight/blob/master/sampleImages/color.png?raw=true)
Depth Mask:
![alt text](https://github.com/Shunxu-H/DayLight/blob/master/sampleImages/depth.png?raw=true)


## TO DO

- [X] Load Cameras from file
- [X] Save pictures
- [X] Redirect output to a FBO and copy it to a texture / save a file,
- [X] Rendering for color and depth images
- [X] Identify objects which can be seem from a particular camera
- [X] Tansformable--'isVisible', filter out invisible objects while rendering
- [X] Standardizing rendering procedures ( render all images given a directory )
- [X] Enlarge .obj data for the depth buffer situation
- [X] Minimize image file ( bit map, text array, lossiless compression)
- [X] Build 'openGl self management'
- [X] Test GLObject(seems working, more tests required)
- [ ] Refracture Code base
  * - [X] Make Class Widget
  * - [X] Make Class View
  * - [ ] Isolate Lumos and Patronus
- [ ] Memory Leak
  * -[X] Loop memory Leak
  * -[ ] Not using global pointer so the destructor is called
	* -[ ] Shaper is taking in Cameras as pointer, which is unnecessary
	* -[ ] Free global resource before exiting
- [ ] Make sure x11 works on the vision machines
- [X] Rebuild GUI
- [ ] build resize event
- [ ] Remake help.txt
- [ ] Copy all necessary files to build directory with CMake
- [X] Propagate mouse event to subviewport
- [ ] Rebuild Navigation with x11
	* - [ ] pan
	* - [ ] tilt
	* - [X] zoom
	* - [X] select
- [X] Make Texture a separated class
- [ ] Make FrameBuffer a separated class
  * - [X] Make FrameBuffer_base
  * - [X] Make FrameBuffer
  * - [ ] Make MultisampledFrameBuffer;
- [ ] Enable more than two shaders in pipes
- [ ] Deffered rendering
	* - [ ] Shadow Mapping
    * - [ ] Make Framebuffer a separated class
	* - [ ] Glow Effect
- [ ] Bullet physic detachable
- [ ] Decide a way to save game state
- [ ] Figure out a better way to fit all objects in frame

## Motivation

1. Headless rendering with OpenGL and X11
2. Game Engine

## Installation

__DEPENDENCY__
1. Bullet physics: http://bulletphysics.org/mediawiki-1.5.8/index.php/Installation
2. OpenGL

For distributions derived from RedHat Linux

```
yum install freeglut-devel
```

For distributions derived from Debian such as Ubuntu

```
apt-get install freeglut3-dev
```


```
mkdir build
cd build
cp -r /path/to/data/dir .
cp -r /path/to/GLSL/dir .
cmake ..
make
./Daylight
```


## API Reference

Read each source file please

## Tests

No tests available at the moment

## Contributors

Shunxu Huang
shunxuhuang@gmail.com

## License

Please refer to LICENSE.txt
