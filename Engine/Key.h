//Copyright 2016, Cameron bell, All rights reserved

#pragma once

#include <SDL\SDL.h>

//Namespace
namespace Penguin
{
	struct Key
	{
		unsigned int SPACE = SDLK_SPACE;

		unsigned int RIGHT = SDLK_RIGHT;
		unsigned int DOWN = SDLK_DOWN;
		unsigned int LEFT = SDLK_LEFT;
		unsigned int UP = SDLK_UP;

		unsigned int NUM_1 = SDLK_1;
		unsigned int NUM_2 = SDLK_2;
		unsigned int NUM_3 = SDLK_3;
		unsigned int NUM_4 = SDLK_4;

		unsigned int BACKSPACE = SDLK_BACKSPACE;

		unsigned int CONTROL = KMOD_CTRL;
		unsigned int SHIFT = KMOD_SHIFT;

		unsigned int A = SDLK_a;
		unsigned int B = SDLK_b;
		unsigned int C = SDLK_c;
		unsigned int D = SDLK_d;
		unsigned int E = SDLK_e;
		unsigned int F = SDLK_f;
		unsigned int G = SDLK_g;
		unsigned int H = SDLK_h;
		unsigned int I = SDLK_i;
		unsigned int J = SDLK_j;
		unsigned int K = SDLK_k;
		unsigned int L = SDLK_l;
		unsigned int M = SDLK_m;
		unsigned int N = SDLK_n;
		unsigned int O = SDLK_o;
		unsigned int P = SDLK_p;
		unsigned int Q = SDLK_q;
		unsigned int R = SDLK_r;
		unsigned int S = SDLK_s;
		unsigned int T = SDLK_t;
		unsigned int U = SDLK_u;
		unsigned int V = SDLK_v;
		unsigned int W = SDLK_w;
		unsigned int X = SDLK_x;
		unsigned int Y = SDLK_y;
		unsigned int Z = SDLK_z;

		unsigned int LEFT_CLICK = SDL_BUTTON_LEFT;
		unsigned int RIGHT_CLICK = SDL_BUTTON_RIGHT;
		unsigned int MIDDLE_CLICK = SDL_BUTTON_MIDDLE;

		unsigned int TILDE = SDLK_BACKSLASH;
	};
}