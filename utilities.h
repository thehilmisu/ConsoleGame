
#include "olcPixelGameEngine.h"
#include <algorithm>
#include <functional>
#include <cmath>

namespace hilmisu{

    class Utilities{
        public:
            struct Rectangle
            {
                float x,y;
                int width,height;
            };
            // A Point structure to represent a point in 2D plane  
            struct Point 
            { 
                float x; 
                float y; 
            }; 
            struct matrix3x3
            {
                float m[3][3];
            };
            // Returns true if the point p is inside the rectangle. 
            bool isInside(Rectangle rect, Point p) 
            { 
                if(p.x >= rect.x && p.x <= (rect.x + rect.width) && 
                    p.y >= rect.y && p.y <= (rect.y + rect.height)) 
                    return true; 
                return false; 
            } 

            static float rand_FloatRange(float a, float b)
            {
                return ((b - a) * ((float)rand() / RAND_MAX)) + a;
            }
            static void Forward(matrix3x3 &mat, float in_x, float in_y, float &out_x, float &out_y)
            {
                out_x = in_x * mat.m[0][0] + in_y * mat.m[1][0] + mat.m[2][0];
                out_y = in_x * mat.m[0][1] + in_y * mat.m[1][1] + mat.m[2][1];
            }
            static olc::vf2d DrawRotatedRectangle(const olc::vf2d& pos, Rectangle rectangle, const float fAngle)
            {
                float x1 = cos(fAngle) * pos.x - sin(fAngle) * pos.y;
                float y1 = sin(fAngle) * pos.x + cos(fAngle) * pos.y;

                return {x1,y1};

            }
            // static olc::vf2d rotate_point(float x,float y,float angle)
            // {
            //     olc::vf2d p;
                
            //     float newX = x * cosf(angle) - y * sinf(angle);
            //     float newY = x * sinf(angle) + y * cosf(angle);

            //     p.x = newX; p.y = newY;
            //     return p;
            // }
            static Point rotate_point(Point p, Point c, float angle) 
            {
                // calculate the sine and cosine of the angle
                double s = std::sin(angle);
                double cx = std::cos(angle);
                // translate point back to origin
                p.x -= c.x;
                p.y -= c.y;
                // rotate the point
                double xnew = p.x * cx - p.y * s;
                double ynew = p.x * s + p.y * cx;
                // translate the point back
                p.x = xnew + c.x;
                p.y = ynew + c.y;
                return p;
            }
            // Function to rotate a rectangle 'rect'
            // around point 'c' by angle 'angle'
            static void rotateRectangle(Rectangle &rect, Point c, float angle)
            {
                // Get corner points
                Point p1 = {rect.x, rect.y};
                Point p2 = {rect.x + rect.width, rect.y};
                Point p3 = {rect.x,
                            rect.y - rect.height};
                Point p4 = {rect.x + rect.width, rect.y -rect.height};

                

                // rotate corner points
                p1 = rotate_point(p1,c, angle);
                p2 = rotate_point(p2,c, angle);
                p3 = rotate_point(p3,c, angle);
                p4 = rotate_point(p4,c, angle);


                // Find new corner points
                rect.x = std::min(p1.x, std::min(p2.x, std::min(p3.x, p4.x)));
                rect.y = std::min(p1.y, std::min(p2.y, std::min(p3.y, p4.y)));

                rect.width = std::max(p1.x, std::max(p2.x, std::max(p3.x, p4.x))) -
                            rect.x;
                rect.height = std::max(p1.y, std::max(p2.y, std::max(p3.y, p4.y))) -
                            rect.y;
            }

    };

}