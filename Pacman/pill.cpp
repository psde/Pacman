#include "pill.hpp"
#include "field.hpp"
#include "game_controller.hpp"

namespace {
PillDescriptor Descriptor = {
	{ 6.0 / 28.0,  6.0 / 28.0, 15.0 / 28.0, 15.0 / 28.0 }
};
}


/**
  * Eine Kirsche erzeugen.
  * @param x X-Position der Zelle des Spielfeldes, in der die Figur
  *          platziert wird.
  * @param y Y-Position der Zelle des Spielfeldes, in der die Figur
  *          platziert wird.
  * @param controller  Spiele-Controller, der die Aktionen
  *                    bewertet und die Figuren steuert.
  */
Pill::Pill(unsigned int x, unsigned int y, GameController* controller):
			Figure(x, y, controller) {
}


/**
  * Aufforderung zur Neuzeichnung.
  * @param window     Verweis auf das Fenster, in dem die Figur
  *                   erscheinen soll.
  * @param cellWidth  Breite einer Zelle auf dem Spielfeld in Pixeln.
  * @param cellHeight Hoehe einer Zelle auf dem Spielfeld in Pixeln.
  */
void Pill::draw(Gosu::Graphics& graphics, int cellWidth, int cellHeight) {

	drawArc(graphics, Gosu::Color(255, 184, 151), cellWidth, cellHeight, true, Descriptor.circle, 0, 360);
}


/**
  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
  * zusammen gestossen.
  * @param otherFigure Anderer Kollisionsbeteiligter.
  */
void Pill::handleCollisionWith(Figure* otherFigure) {
	controller->collisionOfPacmanWith(this);
}
