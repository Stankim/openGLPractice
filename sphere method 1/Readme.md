#Sphere
Make sure you have glad.c, glfw and openGl.

#Compile like this:
g++ drawSphere.cpp glad.c -lglfw

#Limitations
Smoothness can only accept 0 - 8. Any value above that will have so many cordinates to fit in one array.
For full sphere try smoothness of 5 and above.


