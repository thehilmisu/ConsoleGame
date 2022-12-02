
#include "olcPixelGameEngine.h"
#include <algorithm>
#include <functional>
#include <cmath>

namespace hilmisu{

    class Utilities{
        public:
            struct Rectangle
            {
                float x1,y1,x2,y2;
                float width = x2-x1;
                float height = y2-y1;
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
            bool isThereACollision(Rectangle a, Rectangle b) {
                // Check if one rectangle is on the left side of the other
                if (a.x1 > b.x2 || b.x1 > a.x2)
                    return false;

                // Check if one rectangle is above the other
                if (a.y1 > b.y2 || b.y1 > a.y2)
                    return false;

                // If none of the above conditions are true, then there is a collision
                return true;
            }
            // Returns true if the point p is inside the rectangle. 
            bool isInside(Rectangle rect, Point p) 
            { 
                if(p.x >= rect.x1 && p.x <= (rect.x1 + rect.width) && 
                    p.y >= rect.y1 && p.y <= (rect.y1 + rect.height)) 
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
            static olc::vf2d rotate_point(float x,float y,float angle)
            {
                olc::vf2d p;
                
                float newX = x * cosf(angle) - y * sinf(angle);
                float newY = x * sinf(angle) + y * cosf(angle);

                p.x = newX; p.y = newY;
                return p;
            }

    };

}