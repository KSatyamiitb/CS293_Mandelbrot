Author : Kumar Satyam
ROLL NUMBER : 200050064
COURSE : CS293 (CS213 LAB COURSE)
ASSIGNMENT TYPE : COURSE PROJECT 

PROJECT NAME : MANDELBROT SET ZOOM
  
VIDEO LINK : https://drive.google.com/file/d/1VLyYkz2NRaV6PvPGC-MwmyrTFrlt2nhN/view?usp=sharing


 
CONTENTS : README.txt
           main.cpp
           customisations.hpp
           tools.hpp
           tools.cpp
           functions.hpp
           functions.cpp
           area.hpp
           generate.hpp
           generate.cpp




EXTRA LIBRARIES NEEDED : SFML             sudo apt-get install libsfml-dev
                         FreeImage        sudo apt-get install libfreeimage-dev




Compilation Command : g++ tools.cpp generate.cpp functions.cpp main.cpp -lfreeimage -lsfml-graphics -lsfml-window -lsfml-system -lpthread




DESCRIPTION : 
    * Self Adjusting MandelBrot Plot using SFML Graphics and FreeImage Library
    * Using Fractals for the Mandelbrot SET
    * Capture a portion of window using left mouse click and it will get zoomed into
    * To Zoom out press BackSpace 




BRIEF DESIGN PLAN:

# first i have generated an image using the fractal divergence iteration count (< max iteration count) for each complex 
number represented by a pixel color which is generated using the iteration count as a measure by using FreeImage library

# this image is then loaded by texture and then by sprite which displays it on the sfml window

# Zoom In using a rectangle to capture the mandelbrot set , this captured rectangle gets mapped to a new window further for 
which same process as first step is done to get an image and then its loaded as second step

# the parameters indirectly representing the rectangular captures done for zoom in are stored in stack initialised with the 
one representing whole mandelbrot plot

# Zoom Out pops out the stack noe the top data of stack gives paramters for previous display




Referances : SOME YOUTUBE VIDEOS as guide in some fields and geeks for geeks for understanding libraries