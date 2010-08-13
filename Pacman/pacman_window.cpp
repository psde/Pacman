#include "pacman_window.hpp"
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;

PacmanWindow::PacmanWindow() 
			:	Gosu::Window(800, 600, false), 
				font(graphics(), Gosu::defaultFontName(), 20)
{
	this->field = new Field();
}

PacmanWindow::~PacmanWindow() {

}

void PacmanWindow::draw()
{
	if(this->field->getState() == Playing)
	{
		this->field->draw(graphics());
		this->font.draw(L"Points: " + boost::lexical_cast<std::wstring>(this->field->getPoints()), 600, 3, 100);
		this->font.draw(L"Lives: " + boost::lexical_cast<std::wstring>(this->field->getLives()), 600, 16, 100);
	}
	else if(this->field->getState() == Starting)
	{
		this->field->draw(graphics());
		this->font.draw(L"READY!", 265, 350, 100);
	}
	else if(this->field->getState() == LevelOver)
	{
		this->field->draw(graphics());
		this->font.draw(L"Level Over!", 265, 350, 100);
	}
	else if(this->field->getState() == GameOver)
	{
		this->font.draw(L"Game Over", 265, 350, 100);
	}
}

void PacmanWindow::update()
{
	// Ticking
	this->field->nextTick();

	if (this->field->getState() == Playing) {
		Direction keyDirection = Direction::NONE;

		if(input().down(Gosu::kbUp))
		{
			keyDirection = Direction::UP; 
		}

		if(input().down(Gosu::kbDown))
		{
			keyDirection = Direction::DOWN; 
		}

		if(input().down(Gosu::kbLeft))
		{
			keyDirection = Direction::LEFT; 
		}

		if(input().down(Gosu::kbRight))
		{
			keyDirection = Direction::RIGHT; 
		}

		if (keyDirection != Direction::NONE) {
			this->field->keyPressed(keyDirection);
		}
	}
}

void PacmanWindow::buttonDown(Gosu::Button button)
{
	if(button == Gosu::kbEscape)
		close();


	// Input handling
	/*if (!this->field->isGameOver()) {
		Direction keyDirection = Direction::NONE;

		if(button == Gosu::kbUp)
		{
			keyDirection = Direction::UP; 
		}

		if(button == Gosu::kbDown)
		{
			keyDirection = Direction::DOWN; 
		}

		if(button == Gosu::kbLeft)
		{
			keyDirection = Direction::LEFT; 
		}

		if(button == Gosu::kbRight)
		{
			keyDirection = Direction::RIGHT; 
		}

		if (keyDirection != Direction::NONE) {
			this->field->keyPressed(keyDirection);
		}
	}*/
}