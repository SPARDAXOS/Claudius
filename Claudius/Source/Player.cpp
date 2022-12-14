#include "Player.h"
#include <cmath>
#include "RenderManager.h"
#include <iostream>


Player::Player() {
	color.SetColor(0, 255, 0, 0); //Could be just initialized
	rect.SetBounds(0, 0, size, size); //Could be just initialized by game? 

	m_Body.m_Position.x = starting_x;
	m_Body.m_Position.y = starting_y;

	trans.SetPosition(starting_x, starting_y); //Could be just initialized by game? 
	player_score = 0; //Could be just initialized 

	//????? Pooling?
	for (int i = 0; i < player_size; i++)
	{
		parts[i].color.SetColor(255, 0, 0, 0);
		parts[i].rect.SetBounds(0, 0, size, size);
		parts[i].trans.SetPosition(trans.GetX(), trans.GetY());
	}
}


void Player::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, color, trans);

	for (int i = 0; i < player_score; i++)
	{
		renderManager.Render(parts[i].rect, parts[i].color, parts[i].trans);
	}
}

void Player::Update(double dt)
{
	x_array_difference[0] = trans.GetX() - parts[0].trans.GetX();
	y_array_difference[0] = trans.GetY() - parts[0].trans.GetY();

	for (int i = 1; i < (player_size - 1); i++)
	{
			x_array_difference[i] = parts[i].trans.GetX() - parts[i + 1].trans.GetX();
			y_array_difference[i] = parts[i].trans.GetY() - parts[i + 1].trans.GetY();
	}

	if (moving_left == true)
	{
		trans.ChangePosition(-movement_speed, 0);
		parts[0].trans.ChangePosition(x_array_difference[0], y_array_difference[0]);

		for (int i = 1; i < player_size; i++)
		{
			parts[i].trans.ChangePosition(x_array_difference[i - 1], y_array_difference[i - 1]);
		}
	}
	else if (moving_right == true)
	{
		trans.ChangePosition(movement_speed, 0);
		parts[0].trans.ChangePosition(x_array_difference[0], y_array_difference[0]);

		for (int i = 1; i < player_size; i++)
		{
			parts[i].trans.ChangePosition(x_array_difference[i - 1], y_array_difference[i - 1]);
		}
	}
	else if (moving_up == true)
	{
		trans.ChangePosition(0, -movement_speed);
		parts[0].trans.ChangePosition(x_array_difference[0], y_array_difference[0]);

		for (int i = 1; i < player_size; i++)
		{
			parts[i].trans.ChangePosition(x_array_difference[i - 1], y_array_difference[i - 1]);
		}
	}
	else if (moving_down == true)
	{
		trans.ChangePosition(0, movement_speed);
		parts[0].trans.ChangePosition(x_array_difference[0], y_array_difference[0]);

		for (int i = 1; i < player_size; i++)
		{
			parts[i].trans.ChangePosition(x_array_difference[i - 1], y_array_difference[i - 1]);
		}
	}
}

void Player::OnKeyDown(SDL_Keycode key)
{
	if (key == SDLK_LEFT)
	{
		moving_left = true;
		moving_right = false;
		moving_up = false;
		moving_down = false;
	}
	else if (key == SDLK_RIGHT)
	{
		moving_left = false;
		moving_right = true;
		moving_up = false;
		moving_down = false;
	}
	else if (key == SDLK_UP)
	{
		moving_left = false;
		moving_right = false;
		moving_up = true;
		moving_down = false;
	}
	else if (key == SDLK_DOWN)
	{
		moving_left = false;
		moving_right = false;
		moving_up = false;
		moving_down = true;
	}
}

void Player::ResetPlayer()
{
	player_score = 0;
	moving_right = false;
	moving_left = false;
	moving_up = false;
	moving_down = false;

	trans.SetPosition(starting_x, starting_y);
}