# Sphere
Using the sfml library to create a rotating sphere in c++.

NOTE: sfml must be downloaded and properly linked for compiler to make 
an executable file.

Program is used to test the sphere class. Class contains initializer, 
which will initialize the points on the sphere using radius and 
positional difference. The positional difference refers to where 
the sphere should appear on the screen. For the main method, the center
of the screen is used. Both the x and y are required for the initializer to 
accurately initialize points.

The sphere class will provide 3 methods in which the user can rotate along
the x, y, or z axis. After rotating, the method will then call the sort method, 
which will sort using the selection sort algorithm, testing the points along the
z axis. This will allow all points towards the most positive end of the z axis to
be drawn first, providing a more viewable experience for the user.

The give method will allow the user to call specific points in the objects mPoints array. 
Using this will automatically return the point with the positional difference applied to 
either the x or y point. 

For the example, a sphere has been created using an array of sf::CircleShape to create drawable points. 
The sphere uses a 500 distance radius with the positional differences being centered on the screen.
Using a 0.001 rotation angle, the sphere will rotate along the x, y, and z axis. After rotation, 
points will be drawn on screen, given the points along the z axis are above 0. 
