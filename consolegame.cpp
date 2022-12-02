
#define OLC_PGE_APPLICATION
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
		else
		{
			hilmisu::Utilities::Rectangle randomCar;
			randomCar.x = x_value;
			randomCar.y = -50.0f;
			randomCar.width = 10;
			randomCar.height = 40;

			vRects.push_back(randomCar);
		}
		 	
	}

	float speed = 0.0f;
	float max_speed = 1.0f;
	float acceleration = 0.2f;
	float friction = 0.05f;
	float angle = 0.0f;
	float m_angle = 0.0f;

	bool OnUserCreate() override
	{
		hilmisu::Utilities::Rectangle carRectangle;
		carRectangle.x = 120.0f;
		carRectangle.y = 160.0f;
		carRectangle.width = 10;
		carRectangle.height = 40;
		
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
				hilmisu::Utilities::rotateRectangle(vRects[0],center,m_angle);

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

		
		olc::vf2d pos = {vRects[0].x,vRects[0].y} ;
		olc::vi2d size = {vRects[0].width,vRects[0].height} ;

		DrawSprite(pos,sprCar);

		//hilmisu::Utilities::rotateRectangle(vRects[0],center,M_1_PI/2);

		createRandomTraffic(fElapsedTime);


		// Draw all rectangles
		for (int i=0; i< vRects.size();i++)
		{
			olc::vi2d size = {vRects[i].width,vRects[i].height};
			//if(i != 0)//don't draw the 0th index, it is drawed within our calculations above
			DrawRect({static_cast<int>(vRects[i].x),static_cast<int>(vRects[i].y)}, size, olc::WHITE);
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
