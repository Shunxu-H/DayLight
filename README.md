## Synopsis

Daylight is a simple 3d modeling/viewing software built with Qt, OpenGL, Bullet Physics

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

- [X] Fix, Lighting is always a bit too green 
- [ ] Get rid of unwanted functions
- [ ] Shadow mapping 
- [ ] Exploration Camera Mode
- [ ] Wire_frame rendering
- [ ] Highlight on selected object

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

## API Reference

Read each source file please 

## Tests

No tests available at the moment

## Contributors

Shunxu Huang
shunxuhuang@gmail.com

## License

Please refer to LICENSE.txt