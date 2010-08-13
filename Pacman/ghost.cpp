#include "field.hpp"
#include "game_controller.hpp"
#include "ghost.hpp"

namespace {
GhostDescriptor Descriptor = {
	{ 1.0 / 28.0,  0.0,        26.0 / 28.0, 24.0 / 28.0 },  // Head half circle
	{ 1.0 / 28.0, 11.0 / 28.0, 26.0 / 28.0, 12.0 / 28.0 },  // Body rectangle
	{{														// Bottom half circles with animation
		{  2.0 / 28.0, 18.0 / 28.0, 8.0 / 28.0, 8.0 / 28.0 },
		{ 10.0 / 28.0, 18.0 / 28.0, 8.0 / 28.0, 8.0 / 28.0 },
		{ 18.0 / 28.0, 18.0 / 28.0, 8.0 / 28.0, 8.0 / 28.0 }
	},
	{														
		{  6.0 / 28.0, 18.0 / 28.0, 8.0 / 28.0, 8.0 / 28.0 },
		{ 14.0 / 28.0, 18.0 / 28.0, 8.0 / 28.0, 8.0 / 28.0 },
		{ 14.0 / 28.0, 18.0 / 28.0, 8.0 / 28.0, 8.0 / 28.0 }  //HackHack!
	}},
	{ // Array aller Augenrichtungen
		{ // Augen gerade aus (keine Bewegung)
			{{ // Linkes Auge
				{  4.0 / 28.0,  6.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{  6.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			},
			{ // Rechtes Auge
				{ 16.0 / 28.0,  6.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{ 18.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			}}
		},
		{ // Augen hoch
			{{ // Linkes Auge
				{  4.0 / 28.0,  2.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{  6.0 / 28.0,  2.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			},
			{ // Rechtes Auge
				{ 16.0 / 28.0,  2.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{ 18.0 / 28.0,  2.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			}}
		},
		{ // Augen links
			{{ // Linkes Auge
				{  2.0 / 28.0,  6.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{  2.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			},
			{ // Rechtes Auge
				{ 14.0 / 28.0,  6.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{ 14.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			}}
		},
		{ // Augen unten
			{{ // Linkes Auge
				{  4.0 / 28.0,  2.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{  6.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			},
			{ // Rechtes Auge
				{ 16.0 / 28.0,  2.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{ 18.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			}}
		},
		{ // Augen rechts
			{{ // Linkes Auge
				{  6.0 / 28.0,  6.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{ 10.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			},
			{ // Rechtes Auge
				{ 18.0 / 28.0,  6.0 / 28.0, 8.0 / 28.0, 10.0 / 28.0 },
				{ 22.0 / 28.0, 10.0 / 28.0, 4.0 / 28.0,  4.0 / 28.0 }
			}}
		}
	}

};
}

/**
  * Geist erzeugen.
  * @param x X-Position der Zelle des Spielfeldes, in der Geist
  *          platziert wird.
  * @param y Y-Position der Zelle des Spielfeldes, in der Geist
  *          platziert wird.
  * @param controller  Spiele-Controller, der die Aktionen
  *                    bewertet und die Figuren steuert.
  */
Ghost::Ghost(unsigned int x, unsigned int y, GameController* controller)
			:	Figure(x, y, controller) 
{
	this->speed = Ghost::NORMAL_SPEED;
}

/**
  * Aufforderung zur Neuzeichnung. 
  * @param window     Verweis auf das Fenster, in dem die Figur
  *                   erscheinen soll.
  * @param cellWidth  Breite einer Zelle auf dem Spielfeld in Pixeln.
  * @param cellHeight Hoehe einer Zelle auf dem Spielfeld in Pixeln.
  */
void Ghost::draw(Gosu::Graphics& graphics, int cellWidth, int cellHeight) 
{
	// Wenn der Geist harmlos ist, wird die Farbe bei jedem
	// Neuzeichnen veraendert, um einen Blinkeffekt zu erzielen.
	bool harmless = controller->isGhostStateHarmless();
	unsigned int harmlessTicks = controller->getGhostHarmlessTicks();

	Gosu::Color color;
	if(harmless)
	{
		if(harmlessTicks > (GameController::GHOSTS_HARMLESS_TICKS * 0.2f))
		{
			color = Gosu::Color(0, 0, 255);
		}
		else
		{
			color = Gosu::Color(((harmlessTicks % 5) ? 0 : 255), ((harmlessTicks % 5) ? 0 : 255), 255);
		}
	}
	else
	{
		color = Gosu::Color(255, 0, 0);
	}

	if(this->getState() == Alive)
	{
		drawArc(graphics, color, cellWidth, cellHeight, true, Descriptor.topCircle, 0, 180);
		drawRectangle(graphics, color, cellWidth, cellHeight, true, Descriptor.rectangle);
		for (unsigned int i = 0; i < BOTTOM_CIRCLES; ++i) {
			drawArc(graphics, color, cellWidth, cellHeight, true, Descriptor.bottomCircles[(ticks % 5 ? 0 : 1)][ i ], 180, 180);
		}
	}


	Direction dir = direction;
	if(harmless || this->getState() == Dying) dir = Direction::NONE;

	// Beide Augen zeichnen
	for (unsigned int i = 0; i < 2; ++i) {
		drawArc(graphics, Gosu::Color(255, 255, 255), cellWidth, cellHeight, true, Descriptor.eyes[ dir.getValue() ].eye[ i ].outerCircle, 0, 360);
		drawArc(graphics, Gosu::Color(0, 0, 255), cellWidth, cellHeight, true, Descriptor.eyes[ dir.getValue() ].eye[ i ].innerCircle, 0, 360);
	}

	// Wenn Harmlos Mund zeichnen
	if(harmless && this->getState() == Alive)
	{
		for(unsigned int i = 0; i < 6; ++i)
		{
			drawLine(graphics, Gosu::Color(255, 255, 255), cellWidth, cellHeight, 2 + (i * 3), ((i % 2) ? 15 : 18), 5 + (i * 3), (((i+1) % 2) ? 15 : 18));
		}
	}

}

/**
  * Naechster Zeittakt. Die Methode muss uerberschrieben werden,
  * um zeitgesteuerte Aktionen ausloesen zu koennen.
  */
void Ghost::nextTick() {
	if(this->getState() != Dead)
	{
		if(this->getState() == Dying)
		{
			this->speed = Ghost::DEAD_SPEED;
		}
		else if(controller->isGhostStateHarmless())
		{
			this->speed = Ghost::HARMLESS_SPEED;
		}
		else
		{
			this->speed = Ghost::NORMAL_SPEED;
		}

		this->ticks++;
		if(this->ticks >= this->speed)
		{
			this->ticks = 0;
		}
		else
		{
			return;
		}
		
		Direction newDirection;
		unsigned int curIQ = IQ;
		if(this->getState() == Dying) curIQ = DEAD_IQ;

		if (rand() % (unsigned int) ((MAX_IQ-curIQ)/10) == 0) 
		{
			if(this->getState() == Alive)
			{
				newDirection = controller->getDirectionToPacman(this, direction);
			}
			else
			{
				newDirection = controller->getDirectionToCoordinates(this, this->startx, this->starty, direction);
			}

			if (controller->isGhostStateHarmless()) {
				newDirection = newDirection.turn180Degree();
			}
		}
		else 
		{
			do {	// neue Richtung, aber keine Umkehr
				newDirection = Direction::random();
			} while (newDirection == direction.turn180Degree());

			// Weiterdrehen, bis das Feld am Ziel frei ist
			while (!controller->canMove(this, newDirection)) 
			{
				if (newDirection != direction) {
					newDirection = direction;
				}
				else {
					newDirection = Direction::random();
				}
			}
		}

		direction = newDirection;
		controller->move(this, direction);

		if(this->getX() == this->startx && this->getY() == this->starty) 
			this->setState(Alive);
	}
}


/**
  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
  * zusammen gestossen.
  * @param otherFigure Anderer Kollisionsbeteiligter.
  */
void Ghost::handleCollisionWith(Figure* otherFigure) {
	controller->collisionOfPacmanWith(this);
}
