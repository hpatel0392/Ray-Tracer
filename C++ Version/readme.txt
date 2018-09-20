Besides the requirements:
1) IMG_T included
2) Write and cleanup functions included
2) command line used for file IO and augment(s)
3) Reads in from input file all 5 variations (sphere, solid and checkered plane and box)
4) Anti-Aliasing Supersampling (9) 

use Makefile to compile: 
./rt default.txt img.ppm (1) for the default scene and any arguements after the img.pmm (in place of '1') 
                             will execute Anti-Aliasing. ("make default" should also work)

./rt pacman.txt img.ppm (1) for the other scene.
