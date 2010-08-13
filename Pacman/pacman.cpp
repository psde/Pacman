#include "field.hpp"
#include "game_controller.hpp"
#include "pacman.hpp"

namespace {
PacmanDescriptor Descriptor = {
	{ 1.0 / 28.0,  1.0 / 28.0, 26.0 / 28.0, 26.0 / 28.0 }
};
}

/**
  * Pacman erzeugen.
  * @param x X-Position der Zelle des Spielfeldes, in der Pacman
  *          platziert wird.
  * @param y Y-Position der Zelle des Spielfeldes, in der Pacman
  *          platziert wird.
  * @param controller  Spiele-Controller, der die Aktionen
  *                    bewertet und die Figuren steuert.
  */
Pacman::Pacman(unsigned int x, unsigned int y, GameController* controller):
		Figure(x, y, controller) 
{
	this->state = Alive;
	this->speed = Pacman::NORMAL_SPEED;
	reset();
}


/**
  * Aufforderung zur Neuzeichnung.
  * @param window     Verweis auf das Fenster, in dem die Figur
  *                   erscheinen soll.
  * @param cellWidth  Breite einer Zelle auf dem Spielfeld in Pixeln.
  * @param cellHeight Hoehe einer Zelle auf dem Spielfeld in Pixeln.
  */
void Pacman::draw(Gosu::Graphics& graphics, int cellWidth, int cellHeight) 
{
	Gosu::Color foo(255, 255, 0);

	//this->spriteset[mouthStatus]->draw(4 + xOffset + this->cellX * cellWidth, 4 + yOffset + this->cellY * cellHeight, 2);

	/*graphics.drawQuad(xOffset + this->cellX * cellWidth, yOffset + this->cellY * cellHeight, foo,
					  xOffset + this->cellX * cellWidth + cellWidth, yOffset + this->cellY * cellHeight, foo,
					  xOffset + this->cellX * cellWidth, yOffset + this->cellY * cellHeight + cellHeight, foo,
					  xOffset + this->cellX * cellWidth + cellWidth, yOffset + this->cellY * cellHeight + cellHeight, foo, 3);*/
	drawArc(graphics, foo, cellWidth, cellHeight, true, Descriptor.circle, (mouthOpenAngle / 2 + getAngleFromDirection() * 90), (360 - mouthOpenAngle));

/*
	QPainter painter(window);
	// Zeichenfarbe setzen
	painter.setPen(QColor(255, 255, 0));
	painter.setBrush(Qt::SolidPattern);
	painter.setRenderHint(QPainter::Antialiasing);
	// Kreissegment zeichnen
	drawArc(painter, cellWidth, cellHeight,
			true, Descriptor.circle, (mouthOpenAngle / 2 + getAngleFromDirection() * 90), 
			(360 - mouthOpenAngle)); */
}

/**
  * Blickwinkel und damit Richtung bestimmen, in die der
  * Mund zeigen soll. Die Zahl wird als Multiplikator beim
  * Zeichnen verwendet.
  * @return <ul>
  *           <li><code>0</code> = 0 * 90 Grad (rechts)</li>
  *           <li><code>1</code> = 1 * 90 Grad (oben)</li>
  *           <li><code>2</code> = 2 * 90 Grad (links)</li>
  *           <li><code>3</code> = 3 * 90 Grad (unten)</li>
  *         </ul>
  */
unsigned int Pacman::getAngleFromDirection() const {
	switch (direction.getValue()) {
		case Direction::UP:    return 1;
		case Direction::LEFT:  return 2;
		case Direction::DOWN:  return 3;
		case Direction::RIGHT: return 0;
	}

	// Never happens...
	return 0;
}


/**
  * Naechster Zeittakt. Die Methode muss uerberschrieben werden,
  * um zeitgesteuerte Aktionen ausloesen zu koennen.
  */
void Pacman::nextTick() {
	// Mund oeffnen und schliessen
	if (this->state == Alive) {
		if (mouthOpening) {
			mouthOpenAngle += MOUTH_STEP;
			if (mouthOpenAngle == MAX_MOUTH_ANGLE) {
				mouthOpening = false;
			}
		}
		else {
			mouthOpenAngle -= MOUTH_STEP;
			if (mouthOpenAngle == MIN_MOUTH_ANGLE) {
				mouthOpening = true;
			}
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

		// Bewegen
		if (this->direction != Direction::NONE) {
			// Der Controller macht das fuer alle Figuren.
			controller->move(this, this->direction);
		}
	}

	if(this->state == Dying)
	{
		mouthOpenAngle += MOUTH_STEP;
		if(mouthOpenAngle >= 360) this->state = Dead;
	}

}


/**
  * Eine Taste wurde gedrueckt, um die Figur in eine bestimmte
  * Richtung zu schicken. 
  * @param direction Richtung, in die die Figur(en) bewegt werden soll(en).
  */
void Pacman::keyPressed(Direction direction) {
	// Nur weitermachen, wenn Pacman lebt
	if(this->getState() != Alive) return;

	// Neue Richtung speichern
	if (direction != Direction::NONE && controller->canMove(this, direction)) {
		this->direction = direction;
	}
}


/**
  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
  * zusammen gestossen.
  * @param otherFigure Anderer Kollisionsbeteiligter.
  */
void Pacman::handleCollisionWith(Figure* otherFigure) {
	// Keine Aktion: Die anderen Figuren behandeln die
	// Kollision mit Pacman.
}

void Pacman::reset()
{
	Figure::reset();
	this->mouthOpenAngle = MAX_MOUTH_ANGLE;
	this->mouthOpening = false;
	this->direction = Direction::NONE;
}