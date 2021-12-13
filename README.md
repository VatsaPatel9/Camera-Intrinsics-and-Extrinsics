# Camera-Intrinsics-and-Extrinsics
---

## Motivation

Three-dimensional navigation on a static two-dimensional picture utilizing camera intrinsics and extrinsics. There are two pictures, one color and one depth, captured by Kinect, from which the 3D geometry with texture information is reconstructed using the inverse camera model. The 3D scene was then projected onto any arbitrary virtual camera and rendered as a 2D picture. As shown in the following example:

<p align="center">
<img width="600" alt="image" src="https://user-images.githubusercontent.com/63264063/145898542-48115f29-de86-463b-beaf-7bab538825ed.png">
</p>

<p align="center">
<img width="500" alt="image" src="https://user-images.githubusercontent.com/63264063/145898723-9945037a-59a0-4c43-941f-1de2e08d2ab0.png">
</p>

## Data

Two image files:  
(1) "color.jpg" is a standard RGB picture.  
(2) "depth.dat" is a depth file that has the same width and height as the color image. However, the distinction is that each pixel in the depth picture has a depth value rather than a color value. The depth value indicates the distance between the camera center and the associated scene point (measured in cm).  

A Kinect sensor captures both the color and depth images concurrently. As a result, their pixels are already aligned, which implies that for a pixel at (x, y) in the color image, the depth value in the depth image at (x, y). Each pixel value is recorded as "uchar" in the color picture; nevertheless, each pixel value is stored as "short int" in the depth image.

## Usage

(a) Press the 'a' key to translate the camera by ten units along the x-axis.  
(b) Press the 'd' key to translate the camera by -10 units along the x-axis.  
(c) Press the 'w' key to translate the camera by ten units along the y-axis.  
(d) Press the's' key to translate the camera by -10 units along the y-axis.  
(e) Using the 'z' key, adjust the focus length by, for example, +30 pixels.  
(f) Press the 'x' key to lower the focal length by a specified amount, for example, -30 pixels.  
(g) Press the 'r' key to resume the extrinsics of the virtual camera.  
(h) To save the virtual picture to a local file, use the 'o' key.  
I Press the '1' key to rotate the picture clockwise around the x-axis, for example, by 5 degrees.  
(j) Press the '2' key to rotate the picture anti-clockwise around the x-axis, e.g. by 5 degrees.  
(k) Press the '3' key to rotate the picture clockwise around the y-axis, e.g. by 5 degrees.  
(l) Press the '4' key to rotate the picture anti-clockwise around the x-axis, e.g. by 5 degrees.  
(m)Press the '5' key to rotate the camera clockwise around an arbitrary line L, e.g. by 5 degrees. The Line intersects the 3D scene's center and has a direction vector of v = [0.3, 1.0, 0]. This procedure requires the generation of a sequence of matrices.  
(n) Using the '6' key, spin the camera counter-clockwise along the same line L (specified above).  

