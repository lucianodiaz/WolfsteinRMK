# WolfsteinRMK (WIP)

WolfsteinRMK is a remake of the game wolfestein 3d using c++ and SFML.
I made a raycasting system to draw walls and animated sprites.
I follow dev blog https://lodev.org/cgtutor/raycasting.html to understand the structure and implementation also I follow the structure to make a "engine" Following SFML blueprint book.
![Mi video](https://user-images.githubusercontent.com/30010210/207696834-95f8c645-83fa-4d78-9f64-5dde77b0eedc.gif)
![Mi video1](https://user-images.githubusercontent.com/30010210/207697062-6fe7960e-9a02-44d4-aa54-504339535f6b.gif)

## Installation

If you only want run the game you can download the relase version (working in  windows probably in linux too)
This project was made in Visual Studio 22 but if you want you can use another IDE

I use SFML dynamic library so you will need dll's necesary to open from IDE

```bash
Controls
Arrows (up,down) move forward and backward
Arrow (left,right) rotate left, right
Ctrl left shoot.
```

# Content
- Resource Manager
- Input Manager
- Animation Manager
- Scene Manager
- Hierarchy Entity System
- Map load from image (system pixel per pixel)
- Camera 2D (Raycasting)
- Player
- Enemies
- Objects Statics
- Pickup Objects
# Status
This is a WIP (work in proceess) project.
I will add the following
- Dealing damage
- IA for enemies
- Projectile system

## License

[MIT](https://choosealicense.com/licenses/mit/)
