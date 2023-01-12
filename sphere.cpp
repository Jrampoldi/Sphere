#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Sphere
{
    //class creates a sphere using radius, position difference on the screen, and two arrays for storing and changing points on sphere
    private:
        double mRadius;
        double mPoints[6400][3]; //amount of points are set to 
        double tempPoints[6400][3];
        double mPosDiffX; //where on the screen along x
        double mPosDiffY; //where on the screen along y
        double PI = 3.14159265;

        
    public:
        void initialize(double radius, double positionalDiffX, double positionalDiffY)
        {
            //Takes in radius and position difference on window and initializes the points using x, y, and z coordinates
            mRadius = radius;
            mPosDiffX = positionalDiffX;
            mPosDiffY = positionalDiffY;

            int index = 0;
            double lat; //variable for latitude
            double lon; //variable for longitude
            for (int i = 0; i < 80; i++)
            {
                lat = (i - (-2 * PI)) / ((2 * PI) - (-2 * PI));
                for (int j = 0; j < 80; j++)
                {
                    lon = (j - (-PI)) / (PI - (-PI));
                    mPoints[index][0] = (radius * sin(lat) * cos(lon));
                    mPoints[index][1] = (radius * sin(lat) * sin(lon));
                    mPoints[index][2] = (radius * cos(lat));

                    index++;
                }
            }
        }//end of initialize method
        double give(int i, int j)
        {
            //Returns value of array at [i][j] with the positional difference on window
            if (j == 0)
                return mPoints[i][j] + mPosDiffX;
            else if (j == 1)
                return mPoints[i][j] + mPosDiffY;
            else
                return mPoints[i][j];
        }//end of the give method
        void rotateX(double angle)
        {
            //will rotate the sphere along the x axis
            double rotateX[3][3] = {{1, 0, 0},
                                {0, cos(angle), -sin(angle)},
                                {0, sin(angle), cos(angle)}};

            for (int i = 0; i < 6400; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    tempPoints[i][j] = mPoints[i][j];
                    mPoints[i][j] = 0;
                }
            }

            for (int aRow = 0; aRow < 6400; aRow++)
            {
                for (int aColumn = 0; aColumn < 3; aColumn++)
                {
                    for (int bColumn = 0; bColumn < 3; bColumn++)
                    {
                        mPoints[aRow][aColumn] += tempPoints[aRow][bColumn] * rotateX[bColumn][aColumn];
                    }
                }
            }
            this->sortPoints();
        }//end of the rotate x method
        void rotateZ(double angle)
        {
            //will rotate sphere along the z axis
            double rotateZ[3][3] = {{cos(angle), -sin(angle), 0},
                        {sin(angle), cos(angle), 0},
                        {0, 0, 1}};
            for (int i = 0; i < 6400; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    tempPoints[i][j] = mPoints[i][j];
                    mPoints[i][j] = 0;
                }
            }

            for (int aRow = 0; aRow < 6400; aRow++)
            {
                for (int aColumn = 0; aColumn < 3; aColumn++)
                {
                    for (int bColumn = 0; bColumn < 3; bColumn++)
                    {
                        mPoints[aRow][aColumn] += tempPoints[aRow][bColumn] * rotateZ[bColumn][aColumn];
                    }
                }
            }
            this->sortPoints();
        }//end of rotate z method
        void rotateY(double angle)
        {
            //will rotate sphere along y axis
            double rotateY[3][3] = {{cos(angle), 0, sin(angle)},
                                    {0, 1, 0},
                                    {-sin(angle), 0, cos(angle)}};
            for (int i = 0; i < 6400; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    tempPoints[i][j] = mPoints[i][j];
                    mPoints[i][j] = 0;
                }
            }

            for (int aRow = 0; aRow < 6400; aRow++)
            {
                for (int aColumn = 0; aColumn < 3; aColumn++)
                {
                    for (int bColumn = 0; bColumn < 3; bColumn++)
                    {
                        mPoints[aRow][aColumn] += tempPoints[aRow][bColumn] * rotateY[bColumn][aColumn];
                    }
                }
            }
            this->sortPoints();
        }//end of the rotate y method
        void sortPoints()
        {
            //will sort points dependent on the value of z using selection sort
            for (int point = 0; point < 6400; point++)
            {
                double keyX = mPoints[point][0];
                double keyY = mPoints[point][1];
                double keyZ = mPoints[point][2];
                int j = point - 1;
                while ((j > 0) && (mPoints[point][2] < keyZ))
                {
                    mPoints[j + 1][0] = mPoints[j][0];
                    mPoints[j + 1][1] = mPoints[j][1];
                    mPoints[j + 1][2] = mPoints[j][2];
                    j--;
                }
                mPoints[j + 1][0] = keyX;
                mPoints[j + 1][1] = keyY;
                mPoints[j + 1][2] = keyZ;
            }
        }//end of sort points method
};


//test sphere class 
int main()
{
    int ScreenHeight = 1500;
    int ScreenWidth = 2500;
    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Sphere");
    window.setFramerateLimit(60);
    
    //create a sphere object with 500 radius and centered on the screen
    Sphere mySphere;
    mySphere.initialize(500, (ScreenWidth / 2.0), (ScreenHeight / 2.0));

    //create circleshape array with same amount of points
    sf::CircleShape points[6400];

    for (int point = 0; point < 6400; point++)
    {
        points[point].setFillColor(sf::Color(215, 215, 215));
        points[point].setRadius(2);
    }

    double angle = 0.005;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        mySphere.rotateX(angle);
        mySphere.rotateZ(angle);
        mySphere.rotateY(angle);
        mySphere.sortPoints();
        for (int i = 0; i < 6400; i++)
        {
            points[i].setPosition(mySphere.give(i, 0), mySphere.give(i, 1));
        }

        window.clear(sf::Color(20, 20, 20));

        for (int point = 0; point < 6400; point++)
        {
            //if points on the z plane are above 0, draw points.
            //provides a more viewable experience
            if (mySphere.give(point, 2) > 0)
            {
                window.draw(points[point]);
            }
        }

        window.display();

    }

    return 0;
}