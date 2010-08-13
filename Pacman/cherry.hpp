#ifndef CHERRY_H
#define CHERRY_H

#include "figure.hpp"

struct CherryDescriptor {
	BoundingBox cherries[ 2 ];
	BoundingBox reflection[ 4 ];
	BoundingBox stalks[ 2 ];
};

class Cherry: public Figure {
public:
	/**
	  * Eine Kirsche erzeugen.
	  * @param x X-Position der Zelle des Spielfeldes, in der die Figur
	  *          platziert wird.
	  * @param y Y-Position der Zelle des Spielfeldes, in der die Figur
	  *          platziert wird.
	  * @param controller  Spiele-Controller, der die Aktionen
	  *                    bewertet und die Figuren steuert.
	  */
	Cherry(unsigned int x, unsigned int y, GameController* controller);

	/**
	  * Aufforderung zur Neuzeichnung.
	  * @param window     Verweis auf das Fenster, in dem die Figur
	  *                   erscheinen soll.
	  * @param cellWidth  Breite einer Zelle auf dem Spielfeld in Pixeln.
	  * @param cellHeight Hoehe einer Zelle auf dem Spielfeld in Pixeln.
	  */
	virtual void draw(Gosu::Graphics& graphics, int cellWidth, int cellHeight);

	/**
	  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
	  * zusammen gestossen.
	  * @param otherFigure Anderer Kollisionsbeteiligter.
	  */
	virtual void handleCollisionWith(Figure* otherFigure);
};

#endif // CHERRY_H
