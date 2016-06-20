#include "Button.h"

namespace Penguin
{
	Button::Button(Window* rend, Vector pos, Vector s, string letter, string font, Colour tC, Colour bC)
	{
		//Set values
		position = pos;
		scale = s;

		textColour = tC;
		backColour = bC;

		isPressed = false;

		//Position shapes
		Background.Position = position;
		Background.Col = backColour;
		Background.Scale = scale;

		//Text
		Message.Col = textColour;
		Message.Load(rend->GetRenderer(), font, letter, scale.y / 2);
		Message.Position = position;
		Message.Position.x += (Background.Scale.x - Message.Scale.x) / 2;
	}

	void Button::Draw(Window* rend, Input* in)
	{
		//Ususally not pressed
		isPressed = false;

		if (in->GetMousePos().x >= Background.Position.x
			&& in->GetMousePos().y >= Background.Position.y
			&& in->GetMousePos().x <= Background.Position.x + Background.Scale.x
			&& in->GetMousePos().y <= Background.Position.y + Background.Scale.y)
		{
			//Check for click
			if (in->MouseClick(SDL_BUTTON_LEFT)) {
				isPressed = true;
			}

			Background.Col = Colour(100, 100, 100);
		}
		else
		{
			Background.Col = Colour(0, 0, 0);
		}

		Background.Draw(rend, true);
		Message.Draw(rend, true);
	}

	bool Button::pressed()
	{ 
		return isPressed; 
	}
}