## Synopsis

Daylight is a simple 3d modeling/viewing software built with Qt, OpenGL, Bullet Physics
This branch is made to automate data generation process for a paper

## Code Example

Will build this late

## TO DO

- [X] Load Cameras from file 
- [X] Save pictures
- [X] Redirect output to a FBO and copy it to a texture / save a file, 
- [X] Rendering for color and depth images
- [X] Identify objects which can be seem from a particular camera
- [X] Tansformable--'isVisible', filter out invisible objects while rendering
- [X] Standardizing rendering procedures ( render all images given a directory )
- [ ] Enlarge .obj data for the depth buffer situation 

## Motivation

As for right now, I am trying to put together what I have learnt

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

3. Qt : http://doc.qt.io/qt-5/gettingstarted.html

4. In some situation where Qt does not have the most update info for opengl, in my case Intel onbooard GPU under Ubuntu 16.04. Use prefix 

```
MESA_GL_VERSION_OVERRIDE=4.5 ./Daylight
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