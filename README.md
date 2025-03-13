# Low-level Image Processing

A C program for basic image processing operations that works directly with PPM format images without using external libraries.

## Features

This program provides various image processing operations:
- Load PPM images
- Generate random images
- Create images through user input
- Extract and display single color channels (R, G, B)
- Convert to grayscale
- Apply mean blur filter
- Flip images (vertical and horizontal)
- Generate negative images

## Building the Project

```bash
# Clone the repository
git clone https://github.com/noalibi99/Low-level-Image-Processing.git
cd low-level-image-processing

# Build the project
make

# Run the program
./image_processor
```

## Usage

Run the program and follow the interactive menu to select operations:

1. Load a PPM image
2. Generate a random image
3. Create an image through keyboard input
4. Display a single color component
5. Convert to grayscale
6. Apply mean blur filter
7. Perform vertical flip
8. Perform horizontal flip
9. Generate negative image
10. Exit

All processed images are saved to the `output/` directory.

## File Format

This program works with PPM (P3) format images, which are plain text files with the following structure:
```
P3
width height
255
r g b r g b r g b ...
```

## Example

```bash
# Load an image and apply a blur filter
./image_processor
# Choose option 1, enter the path to your image
# Choose option 6, enter kernel size (e.g., 3)
# The blurred image will be saved to output/blurred_image.ppm
```
