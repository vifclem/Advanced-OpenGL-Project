#pragma once
class Color {
	
public:
	float r, g, b, a;
	enum Colors
	{
		WHITE,
		BLACK,
		GREY,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		ORANGE,
		PINK
	};

	Color(){
		SetColor(BLACK);
	}
	Color(float rP, float gP, float bP, float aP = 1) {
		SetColor(rP, gP, bP, aP);
	}

	Color(Colors preset) {
		SetColor(preset);
	}

	

	void SetColor(float rP, float gP, float bP, float aP = 1) {
		r = rP;
		g = gP;
		b = bP;
		a = aP;
	}

	void SetColor(Colors colorP, float alphaP = 1) {
		switch (colorP)
		{
		case Color::WHITE:
			SetColor(1, 1, 1, alphaP);
			break;
		case Color::BLACK:
			SetColor(0, 0, 0, alphaP);
			break;
		case Color::GREY:
			SetColor(0.5, 0.5, 0.5, alphaP);
			break;
		case Color::RED:
			SetColor(1, 0, 0, alphaP);
			break;
		case Color::GREEN:
			SetColor(0, 1, 0, alphaP);
			break;
		case Color::BLUE:			
			SetColor(0, 0, 1, alphaP);
			break;
		case Color::YELLOW:
			SetColor(1, 1, 0, alphaP);
			break;
		case Color::ORANGE:
			SetColor(1, 0.65, 0, alphaP);
			break;
		case Color::PINK:
			SetColor(1, 0.41, 0.7, alphaP);
			break;
		default:
			break;
		}
	}

	
};