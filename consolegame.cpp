
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
	olc::Sprite *sprCar;
	
public:
	void createRandomTraffic(float fElapsedTime)
	{
		float x_value = hilmisu::Utilities::rand_FloatRange(50.0f, 160.0f);
		// to do
		if (vRects.size() > 1)
		{
			if (vRects[1].pos.y > 240)
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
		//vRects.push_back({{50.0f, 0.0f}, {1.0f, 1000.0f}});	  // left wall
		//vRects.push_back({{200.0f, 0.0f}, {1.0f, 1000.0f}});  // right wall

		
		sprCar = new olc::Sprite("car_top1_resized.png");

		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::DARK_BLUE);
		SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency

		DrawLine(50,500,50,-500); //left wall
		DrawLine(200,500,200,-500); //right wall

		

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


		float cx = vRects[0].size.x / 2;
		float cy = vRects[0].size.y / 2;

		olc::vf2d half_dims(cx,cy);
		olc::vf2d tr(-cx,cy);
		olc::vf2d br(-cx,-cy);
		olc::vf2d bl(cx,-cy);
		olc::vf2d tl(cx,cy);

		if (speed != 0.0f)
		{
			if((GetKey(olc::Key::A).bHeld) || (GetKey(olc::Key::D).bHeld))
			{
				if (GetKey(olc::Key::A).bHeld)
				{
					m_angle += -0.01f;
				}
				if (GetKey(olc::Key::D).bHeld)
				{
					m_angle += 0.01f;
				}
				//m_angle = 45;

			}

		}
		else if(speed == 0.0f)
		{
			//what happens when speed is 0 ???
			if(m_angle < 0.0f)
			{
				m_angle += 0.01f
			}
			else if(m_angle > 0.0f)
			{
				m_angle -= 0.01f;
			}
			else
				m_angle = 0;
			
		}

		tl = (hilmisu::Utilities::rotate_point(tl.x,tl.y,m_angle) + half_dims + vRects[0].pos);
		bl = (hilmisu::Utilities::rotate_point(bl.x,bl.y,m_angle) + half_dims + vRects[0].pos);
		br = (hilmisu::Utilities::rotate_point(br.x,br.y,m_angle) + half_dims + vRects[0].pos);
		tr = (hilmisu::Utilities::rotate_point(tr.x,tr.y,m_angle) + half_dims + vRects[0].pos);

		DrawSprite(bl,sprCar);

		//collision detection to walls
		// if(br.x <= 50.0f || tr.x <= 50.0f) {
		// 	std::cout << "hit the leftWall" << std::endl;
		// 	br.x = 50.0f;
		// 	tr.x = 50.0f;
		// }
			
		// if(bl.x >= 200.0f || tl.x >= 200.0f){
		// 	std::cout << "hit the rightWall" << std::endl;
		// 	bl.x = 200.0f;
		// 	tl.x = 200.0f;
		// } 

		DrawLine(tl,tr);
		DrawLine(tl,bl);
		DrawLine(bl,br);
		DrawLine(tr,br);

		createRandomTraffic(fElapsedTime);


		// Draw all rectangles
		for (int i=0; i< vRects.size();i++)
		{
			if(i != 0)//don't draw the 0th index, it is drawed within our calculations above
				DrawRect(vRects[i].pos, vRects[i].size, olc::WHITE);
		}

		vRects[1].pos.y += max_speed * fElapsedTime * 5;

		vRects[0].pos.x += speed * sinf(m_angle);
		vRects[0].pos.y -= speed * cosf(m_angle);

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
