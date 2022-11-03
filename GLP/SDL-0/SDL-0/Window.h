#pragma once
#include "Vector2Int.h"
#include "Color.h"
#include <SDL.h>
#include "glew.h"

class Window
{
private:
	Vector2Int m_windowSize;
	SDL_Window* m_window;
	SDL_GLContext m_context;
	Color m_backgroundColor;


public:
	Window(int width=1000, int height=700, Color colorP = Color::BLUE);
	~Window(){}

	void ChangeBackgroundColor(Color color);
	void ChangeBackgroundColor(float rP, float gP, float bP, float aP);
	void PaintBackground();
	void Update();
	void Close();
};

