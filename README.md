# cub3D

In this project, inspired by the iconic Wolfenstein 3D, you will create a dynamic, first-person perspective view inside a maze using ray-casting. It’s an opportunity to explore computer graphics, mathematics, and algorithm design while honing your C programming skills.

---

## Learning Outcomes

Through this project, you will:
- Gain hands-on experience with ray-casting principles.
- Enhance your understanding of graphics programming using the MLX42 library.
- Improve your skills in algorithm design, resource management, and debugging.
- Learn to handle real-world constraints such as smooth window management and efficient parsing.

---

## Mandatory Features

Your program will simulate a 3D view inside a maze with the following functionalities:

1. **Rendering:**
   - Realistic 3D representation of a maze using ray-casting.
   - Textures for walls that vary by orientation (North, South, East, West).
   - Distinct floor and ceiling colors.

2. **User Interaction:**
   - Move through the maze using `W`, `A`, `S`, and `D` keys.
   - Rotate the view using the left and right arrow keys.
   - Exit cleanly via the `ESC` key or window controls.

3. **Map Parsing:**
   - Input a `.cub` file describing the maze layout, textures, and colors.
   - Validate the map for proper structure and closed boundaries.

4. **Error Handling:**
   - Display clear error messages for invalid configurations or files.

5. **Other features:**
   - Wall collision detection.
   - A minimap overlay.
   - Doors that open and close.
   - Animated sprites.
   - Mouse-based viewpoint rotation.
   - Enemies


---

## Usage

1. Compile the project with the Makefile:
2. Execute the program with a `.cub` file as input:
   ```bash
   ./cub3D map.cub
   ```
3. Example `.cub` file (there is several in the "mappies" directory:
```text
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
111111
100001
1010N1
111111
