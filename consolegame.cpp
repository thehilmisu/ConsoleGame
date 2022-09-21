
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <algorithm>
#include <functional>
#include <cmath>
struct rect
{
	olc::vf2d pos;
	olc::vf2d size;
};
class RectangleCollisions : public olc::PixelGameEngine
{
public:
	RectangleCollisions()
	{
		sAppName = "Rectangles!";
	}

	std::vector<rect> vRects;

public:

	bool checkcollisiononeway(rect rect1, rect rect2)
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

	bool checkcollisionbothways(rect rectA, rect rectB)
	{
		return checkcollisiononeway(rectA, rectB) || checkcollisiononeway(rectB, rectA);
	}

	float rand_FloatRange(float a, float b)
	{
		return ((b - a) * ((float)rand() / RAND_MAX)) + a;
	}

	void createRandomTraffic(float fElapsedTime)
	{
		float x_value = rand_FloatRange(50.0f, 160.0f);
		// std::cout << vRects.size() << std::endl;
		// to do
		if (vRects.size() > 3)
		{
			if (vRects[3].pos.y > 240)
				vRects.pop_back();
		}
		else
			vRects.push_back({{x_value, -50.0f}, {10.0f, 40.0f}});
	}

	olc::vf2d DrawRotatedRectangle(const olc::vf2d& pos, rect rectangle, const float fAngle)
	{
		float x1 = cos(fAngle) * pos.x - sin(fAngle) * pos.y;
		float y1 = sin(fAngle) * pos.x + cos(fAngle) * pos.y;

		return {x1,y1};

	}
	olc::vf2d rotate_point(float x,float y,float angle)
	{
		olc::vf2d p;
		
		float newX = x * cosf(angle) - y * sinf(angle);
		float newY = x * sinf(angle) + y * cosf(angle);

		p.x = newX; p.y = newY;
		return p;
	}
	olc::vf2d rotate_point_new(float cx, float cy, float angle, olc::vf2d p){
	  olc::vf2d ret(cos(angle) * (p.x - cx) - sin(angle) * (p.y - cy) + cx,
                  sin(angle) * (p.x - cx) + cos(angle) * (p.y - cy) + cy);
     return ret;
	}

	float speed = 0.0f;
	float max_speed = 3.0f;
	float acceleration = 0.2f;
	float friction = 0.05f;
	float angle = 0.0f;
	float m_angle = 0.0f;

	bool OnUserCreate() override
	{
		vRects.push_back({{120.0f, 160.0f}, {10.0f, 40.0f}}); // car rectangle
		vRects.push_back({{50.0f, 0.0f}, {1.0f, 1000.0f}});	  // left wall
		vRects.push_back({{200.0f, 0.0f}, {1.0f, 1000.0f}});  // right wall
		// vRects.push_back({ {170.0f, 50.0f}, {20.0f, 20.0f} });
		// vRects.push_back({ {190.0f, 50.0f}, {20.0f, 20.0f} });
		// vRects.push_back({ {110.0f, 50.0f}, {20.0f, 20.0f} });
		// vRects.push_back({ {50.0f, 130.0f}, {20.0f, 20.0f} });
		// vRects.push_back({ {50.0f, 150.0f}, {20.0f, 20.0f} });
		// vRects.push_back({ {50.0f, 170.0f}, {20.0f, 20.0f} });
		// vRects.push_back({ {150.0f, 100.0f}, {10.0f, 1.0f} });
		// vRects.push_back({ {200.0f, 100.0f}, {20.0f, 60.0f} });

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_BLUE);

		if (GetKey(olc::Key::W).bHeld)
			speed += acceleration;
		if (GetKey(olc::Key::S).bHeld)
			speed -= acceleration;

		if (speed > max_speed)
		{
			speed = max_speed;
		}
		if (speed < -max_speed / 2)
		{
			speed = -max_speed / 2;
		}

		if (speed > 0.0f)
		{
			speed -= friction;
		}
		else if (speed < 0.0f)
		{
			speed += friction;
		}
		if (abs(speed) < friction)
		{
			speed = 0;
		}
		int direction = 0;
		if (speed != 0.0f)
		{
			

				//std::cout << "###########" << newCoordinates.x << newCoordinates.y << m_angle << std::endl;
		

		}
		else if(speed == 0.0f)
		{
			
			if((GetKey(olc::Key::A).bHeld) || (GetKey(olc::Key::D).bHeld))
			{
				if (GetKey(olc::Key::A).bHeld)
				{
					direction = 1;
					m_angle += -0.03f;
				}
				if (GetKey(olc::Key::D).bHeld)
				{
					direction = 0;
					m_angle += 0.03f;
				}
				//m_angle = 45;
				float cx = vRects[0].size.x / 2;

				float cy = vRects[0].size.y / 2;

				olc::vf2d half_dims(cx,cy);
				olc::vf2d tl(-cx,cy);
				olc::vf2d bl(-cx,-cy);
				olc::vf2d br(cx,-cy);
				olc::vf2d tr(cx,cy);

				tl = (rotate_point(tl.x,tl.y,m_angle) + half_dims + vRects[0].pos);
				bl = (rotate_point(bl.x,bl.y,m_angle) + half_dims + vRects[0].pos);
				br = (rotate_point(br.x,br.y,m_angle) + half_dims + vRects[0].pos);
				tr = (rotate_point(tr.x,tr.y,m_angle) + half_dims + vRects[0].pos);

				//vRects[0].pos = tl;


				DrawLine(tl,tr);
				DrawLine(tl,bl);
				DrawLine(bl,br);
				DrawLine(tr,br);


				
				// DrawLine(temp5,temp6);
					}
		}

		createRandomTraffic(fElapsedTime);

		// Update the player rectangles position, with its modified velocity
		// if(direction == 0)
		// 	vRects[0].pos.x +=  speed ;
		// else
		// 	vRects[0].pos.x -=  speed ;

		//vRects[0].pos.y -=  speed ;

		//std::cout << checkcollisionbothways(vRects[0],vRects[1]) << std::endl;

		//vRects[0].pos -= {(sin(angle)) * speed, (cos(angle)) * speed};

		//std::cout << sinf(angle) * speed << "  #############  " << cosf(angle) * speed  << std::endl;

		// Draw all rectangles
		for (const auto &r : vRects)
			DrawRect(r.pos, r.size, olc::WHITE);


		vRects[3].pos.y += max_speed * fElapsedTime * 5;


		return true;
	}
};


int main()
{
	RectangleCollisions demo;
	if (demo.Construct(256, 240, 4, 4, false, false))
		demo.Start();
	return 0;
}

//olc::vf2d newCoordinates =  rotate_point_new(cx,cy,m_angle,vRects[0].pos);
				// olc::vf2d newCoordinates =  rotate_point(cx,cy,m_angle);



				// olc::vf2d temp = vRects[0].pos;



				// temp.x = temp.x + vRects[0].size.x;
				// temp.y = vRects[0].pos.y;

				// olc::vf2d temp2 = newCoordinates;
				// temp2.x = temp2.x + vRects[0].size.x;
				// temp2.y = newCoordinates.y;

				// olc::vf2d temp3 = newCoordinates;
				// temp3.x = vRects[0].pos.x;
				// temp3.y = vRects[0].pos.y + vRects[0].size.y;

				// olc::vf2d temp4 = newCoordinates;
				// temp4.x = newCoordinates.x;
				// temp4.y = newCoordinates.y+vRects[0].size.y;

				// olc::vf2d temp5 = newCoordinates;
				// temp5.x = vRects[0].pos.x + vRects[0].size.x;
				// temp5.y = vRects[0].pos.y + vRects[0].size.y;

				// olc::vf2d temp6 = newCoordinates;
				// temp6.x = newCoordinates.x + vRects[0].size.x;
				// temp6.y = newCoordinates.y+vRects[0].size.y;

				// DrawLine(vRects[0].pos,newCoordinates);
				// DrawLine(temp,temp2);
				// DrawLine(temp3,temp4);
