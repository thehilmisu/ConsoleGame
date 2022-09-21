
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

            static bool checkcollisionbothways(rect rectA, rect rectB)
            {
                return checkcollisiononeway(rectA, rectB) || checkcollisiononeway(rectB, rectA);
            }

            static float rand_FloatRange(float a, float b)
            {
                return ((b - a) * ((float)rand() / RAND_MAX)) + a;
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