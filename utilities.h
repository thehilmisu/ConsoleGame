
#include "olcPixelGameEngine.h"
#include <algorithm>
#include <functional>
#include <cmath>

namespace hilmisu{

    class Utilities{
        public:
            struct rect
            {
                olc::vf2d pos;
                olc::vf2d size;
            };
            struct matrix3x3
            {
                float m[3][3];
            };
            static bool checkcollisiononeway(rect rect1, rect rect2)
            {
                if (rect1.pos.x < rect2.pos.x + rect2.size.x &&
                    rect1.pos.x + rect1.size.x > rect2.pos.x &&
                    rect1.pos.y < rect2.pos.y + rect2.size.y &&
                    rect1.size.y + rect1.pos.y > rect2.pos.y)
                {
                    return true;
                }
                return false;
            }
            static bool checkcollisiononeway(float x1, float y1, float width1, float height1, 
                                             float x2, float y2, float width2, float height2)
            {
                if (x1 < x2 + width2 &&
                    x1 + width1 > x2 &&
                    y1 < y2 + height2 &&
                    height1 + y1 > y2)
                {
                    return true;
                }
                return false;
            }

            static bool checkcollisionbothways(rect rectA, rect rectB)
            {
                return checkcollisiononeway(rectA, rectB) || checkcollisiononeway(rectB, rectA);
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
            static olc::vf2d DrawRotatedRectangle(const olc::vf2d& pos, rect rectangle, const float fAngle)
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