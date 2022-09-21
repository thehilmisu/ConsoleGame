
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "utilities.h"
#include <algorithm>
#include <functional>
#include <cmath>

class ConsoleGame : public olc::PixelGameEngine
{
public:
	ConsoleGame()
	{
		sAppName = "Rectangles!";
	}

	std::vector<hilmisu::Utilities::rect> vRects;

public:
	void createRandomTraffic(float fElapsedTime)
	{
		float x_value = hilmisu::Utilities::rand_FloatRange(50.0f, 160.0f);
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

				tl = (hilmisu::Utilities::rotate_point(tl.x,tl.y,m_angle) + half_dims + vRects[0].pos);
				bl = (hilmisu::Utilities::rotate_point(bl.x,bl.y,m_angle) + half_dims + vRects[0].pos);
				br = (hilmisu::Utilities::rotate_point(br.x,br.y,m_angle) + half_dims + vRects[0].pos);
				tr = (hilmisu::Utilities::rotate_point(tr.x,tr.y,m_angle) + half_dims + vRects[0].pos);

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
	ConsoleGame game;
	if (game.Construct(256, 240, 4, 4, false, false))
		game.Start();
	return 0;
}
