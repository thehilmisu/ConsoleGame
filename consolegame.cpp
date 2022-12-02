
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

	std::vector<hilmisu::Utilities::Rectangle> vRects;
	olc::Sprite *sprCar;
	
public:
	void createRandomTraffic(float fElapsedTime)
	{
		float x_value = hilmisu::Utilities::rand_FloatRange(50.0f, 160.0f);
		// to do
		if (vRects.size() > 1)
		{
			if (vRects[1].y > 240)
				vRects.pop_back();
		}
		// else
		// 	vRects.push_back({{x_value, -50.0f}, {10.0f, 40.0f}});
	}

	float speed = 0.0f;
	float max_speed = 3.0f;
	float acceleration = 0.2f;
	float friction = 0.05f;
	float angle = 0.0f;
	float m_angle = 0.0f;

	bool OnUserCreate() override
	{
		hilmisu::Utilities::Rectangle carRectangle;
		carRectangle.x = 120.0f;
		carRectangle.y = 160.0f;
		carRectangle.width = 10.0f;
		carRectangle.height = 40.0f;
		
		vRects.push_back(carRectangle); // car rectangle
		
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


		float cx = vRects[0].width / 2;
		float cy = vRects[0].height / 2;

		hilmisu::Utilities::Point center{cx,cy};


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
				m_angle += 0.01f;
			}
			else if(m_angle > 0.0f)
			{
				m_angle -= 0.01f;
			}
			else
				m_angle = 0;
			
		}

		

		hilmisu::Utilities::rotateRectangle(vRects[0],center,m_angle);
		olc::vf2d pos = {vRects[0].x,vRects[0].y} ;
		olc::vf2d size = {vRects[0].width,vRects[0].height} ;

		DrawRect(pos, size, olc::WHITE);

		DrawSprite(pos,sprCar);

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

		// DrawLine(tl,tr);
		// DrawLine(tl,bl);
		// DrawLine(bl,br);
		// DrawLine(tr,br);

		createRandomTraffic(fElapsedTime);


		// Draw all rectangles
		for (int i=0; i< vRects.size();i++)
		{
			if(i != 0)//don't draw the 0th index, it is drawed within our calculations above
				DrawRect({vRects[i].x,vRects[i].y}, {vRects[i].width,vRects[i].height}, olc::WHITE);
		}

		vRects[1].y += max_speed * fElapsedTime * 5;

		vRects[0].x += speed * sinf(m_angle);
		vRects[0].y -= speed * cosf(m_angle);

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
