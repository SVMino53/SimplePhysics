// SimplePhysics
// Created by Isak "Mino53" Forsberg
// V. 0.0, 2024-01-15

#include <SDL.h>

constexpr auto PI = 3.14159265359;
constexpr auto TAU = 6.28318530718;



class Circle
{
	float x, y, r;
	float lineWidth;
	SDL_Color lineCol;
	SDL_Color fillCol;

public:
	Circle()
	{
		x = 0.0f;
		y = 0.0f;
		r = 10.0f;
		lineWidth = 1.0f;
		lineCol = { 0, 0, 0, 255 };
		fillCol = { 255, 255, 255, 255 };
	}
	
	void SetPos(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void SetRadius(float r)
	{
		this->r = r;
	}
	void SetLineWidth(float w)
	{
		lineWidth = w;
	}
	void SetLineColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		lineCol = { r, g, b, a };
	}
	void SetFillColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		fillCol = { r, g, b, a };
	}

	void Translate(float x, float y)
	{
		this->x += x;
		this->y += y;
	}
	void Scale(float percent)
	{
		r *= percent;
	}

	double GetXPos()
	{
		return x;
	}
	double GetYPos()
	{
		return y;
	}
	double GetRadius()
	{
		return r;
	}

	void Render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, fillCol.r, fillCol.g, fillCol.b, fillCol.a);
		for (int i = -(int)r - 1; i <= (int)r; i++)
		{
			for (int j = -(int)r - 1; j <= (int)r; j++)
			{
				if (powf((float)i, 2.0f) + powf((float)j, 2.0f) <= powf(r, 2.0f))
				{
					SDL_RenderDrawPoint(renderer, (int)x + i, (int)y + j);
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, lineCol.r, lineCol.g, lineCol.b, lineCol.a);
		for (int i = -(int)r - (int)(lineWidth / 2.0f) - 1; i <= (int)r + (int)(lineWidth / 2.0f); i++)
		{
			for (int j = -(int)r - (int)(lineWidth / 2.0f) - 1; j <= (int)r + (int)(lineWidth / 2.0f); j++)
			{
				if (fabsf(r - sqrtf(powf((float)i, 2.0f) + powf((float)j, 2.0f))) <= lineWidth / 2.0f)
				{
					SDL_RenderDrawPoint(renderer, (int)x + i, (int)y + j);
				}
			}
		}
	}
};


int main(int argc, char* args[])
{
	SDL_Window* window = SDL_CreateWindow("SimplePhysics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	Circle c = Circle();
	c.SetPos(500, 250);
	c.SetRadius(30);
	c.SetLineWidth(5);
	c.SetFillColor(255, 100, 0, 255);

	bool quit = false;

	while (!quit)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			default:
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 50, 0, 50, 255);
		SDL_RenderClear(renderer);

		c.Translate(0.3, 0.1);
		c.Render(renderer);

		SDL_RenderPresent(renderer);
	}


	return 0;
}