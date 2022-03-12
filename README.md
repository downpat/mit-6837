# mit-6837
My implementations of the assignments from MIT OCW 6.837

## Building assignment zero
The PDF for MIT 6.837 Assignment Zero is at assignments/zero/MIT6_837F12_assn0.pdf. It will not build out-of-the-box on a linux system. You will need to install MIT's vecmath at /usr/include/vecmath and /usr/lib/libvecmath.so in order for this code to work. Perhaps a future version of this repository will build it automatically.

The https://github.com/ydm/mit-vecmath repository will install vecmath for you. Simply download it onto any linux machine and run `make` and `make install`.

The Makefile of this repository has been updated for use with the new vecmath dependency location. If you found this page because you were unable to build assignment zero, update your Makefile accordingly.

The first assignment also contains two helper functions (glVertex and glNormal) that are improperly defined and cause the compiler to fail. Those functions are commented out and the assignment runs fine without them.
