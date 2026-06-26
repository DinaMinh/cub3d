*This project has been created as part of the 42 curriculum by dminh, ebourdet.*

## Description
This project is cub3D, a graphics project inspired by the world-famous Wolfenstein 3D game. The goal is to create a dynamic 3D graphical representation of the inside of a maze from a first-person perspective using ray-casting principles. All constraints and requirements for this project are outlined in the en.subject.pdf file. 

The program handles window management smoothly and displays different wall textures based on the wall's facing direction (North, South, East, West). The floor and ceiling colors can be set to two different colors.

## Features
* **Movement**: The W, A, S, and D keys allow you to move the point of view through the maze.
* **Camera**: The left and right arrow keys allow you to look left and right.
* **Clean Exit**: Pressing ESC or clicking the red cross on the window's frame closes the window and quits the program cleanly.
* **Map Parsing**: The program takes a `.cub` scene description file as its first argument.
* **Bonuses Implemented**:
  * Wall collisions.
  * A minimap system.
  * Doors which can open and close.
  * Animated sprites, including sword animations.
  * Rotate the point of view with the mouse.

## Instructions
* **Compilation**: A `Makefile` is provided to compile the source files into the required binary using `cc`. The flags `-Wall`, `-Wextra`, and `-Werror` are strictly applied.
* Run `make` to compile the `cub3D` binary.
* Other available rules are `all`, `clean`, `fclean`, `re`, and a `debug` target.
* **Execution**: Run the program by passing a valid map file as an argument.
    ```bash
    ./cub3D map/test.cub
    ```

## Resources
-[3D Sage Raycaster vids](https://www.youtube.com/playlist?list=PLMTDxt7L_MNXx7QP80seZUfcSoJ4jl34D)
-[lodev Raycasting explanation](https://lodev.org/cgtutor/raycasting.html)
* The project uses the **miniLibX** graphics library.
* Mathematics and ray-casting algorithms were developed using various documents available on the internet as a tool to create elegant and efficient algorithms.
* **AI Usage**: AI tools were used during this project to reduce repetitive or tedious tasks, assist with documentation, and aid in exploring ray-casting logic. Peer review was utilized to systematically check and validate AI-generated approaches.
