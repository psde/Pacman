#include "cherry.hpp"
#include "field.hpp"
#include "game_controller.hpp"

namespace {
CherryDescriptor Descriptor = {
	{
		{  2.0 / 28.0, 10.0 / 28.0, 12.0 / 28.0, 12.0 / 28.0 }, 
		{ 12.0 / 28.0, 14.0 / 28.0, 12.0 / 28.0, 12.0 / 28.0 }
	},
	{
		{  4.0 / 28.0, 16.0 / 28.0,  2.5 / 28.0,  2.5 / 28.0 }, 
		{  6.0 / 28.0, 18.0 / 28.0,  2.5 / 28.0,  2.5 / 28.0 }, 
		{ 14.0 / 28.0, 20.0 / 28.0,  2.5 / 28.0,  2.5 / 28.0 }, 
		{ 16.0 / 28.0, 22.0 / 28.0,  2.5 / 28.0,  2.5 / 28.0 }
	},
	{
		{  8.0 / 28.0,  8.0 / 28.0, 28.0 / 28.0, 24.0 / 28.0 }, 
		{ 16.0 / 28.0,  8.0 / 28.0, 20.0 / 28.0, 20.0 / 28.0 }
	}
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
Cherry::Cherry(unsigned int x, unsigned int y, GameController* controller):
			Figure(x, y, controller) {
}


/**
  * Aufforderung zur Neuzeichnung.
  * @param window     Verweis auf das Fenster, in dem die Figur
  *                   erscheinen soll.
  * @param cellWidth  Breite einer Zelle auf dem Spielfeld in Pixeln.
  * @param cellHeight Hoehe einer Zelle auf dem Spielfeld in Pixeln.
  */
void Cherry::draw(Gosu::Graphics& graphics, int cellWidth, int cellHeight) {
	// die Stiele
	for (int i = 0; i < 2; i++) {
		drawArc(graphics, Gosu::Color(255, 128, 64), cellWidth, cellHeight, false, Descriptor.stalks[ i ], 90, 70);
	}

	// die Fruechte selbst
	for (int i = 0; i < 2; i++) {
		drawArc(graphics, Gosu::Color(204, 0, 0), cellWidth, cellHeight, true, Descriptor.cherries[ i ], 0, 360);
	}

	// die Reflektionen auf den Fruechten
	for (int i = 0; i < 4; i++) {
		drawArc(graphics, Gosu::Color(255, 255, 255), cellWidth, cellHeight, true, Descriptor.reflection[ i ], 0, 360);
	}
}


/**
  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
  * zusammen gestossen.
  * @param otherFigure Anderer Kollisionsbeteiligter.
  */
void Cherry::handleCollisionWith(Figure* otherFigure) {
	controller->collisionOfPacmanWith(this);
}
