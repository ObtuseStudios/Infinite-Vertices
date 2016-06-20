#pragma once

#include "Text.h"
#include "Rectangle.h"

namespace Penguin
{
	class Button
	{
	public:
		Button(Window* rend, Vector pos, Vector s, string message, string fontPath, Colour tC = Colour(255, 255, 255), Colour bC = Colour(0, 0, 0));
		void Draw(Window* rend, Input* in);

		bool pressed();

		void setPosition(Vector a) 
		{ 
			Background.Position = a; 
			Message.Position = a;
			Message.Position.y += scale.y / 5;
			Message.Position.x += (Background.Scale.x - Message.Scale.x) / 2;
		}
		Vector position;
		Vector scale;

	private:
		Text Message;
		Rectangle Background;

		Colour textColour;
		Colour backColour;

		bool isPressed;

	};
}