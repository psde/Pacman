#ifndef GHOST_H
#define GHOST_H

#include <Gosu/Gosu.hpp>
#include "figure.hpp"

struct Eye {
	BoundingBox outerCircle;
	BoundingBox innerCircle;
};

struct Eyes {
	Eye eye[ 2 ];
};

const unsigned int BOTTOM_CIRCLES = 3;
const unsigned int DIRECTIONS = 5;

struct GhostDescriptor {
	BoundingBox topCircle;
	BoundingBox rectangle;
	BoundingBox bottomCircles[2][ BOTTOM_CIRCLES ];
	//BoundingBox bottomCircles2[ BOTTOM_CIRCLES ];
	Eyes        eyes[ DIRECTIONS ]; // fuer alle Bewegungsrichtungen (keine, up, left, down, right)
};

class Ghost: public Figure {
	// 'Intelligenz' festlegen (0-190 als Hinweis
	// auf die Qualitaet, mit der sie Pacman folgen).
	// Der Wert darf nicht hoeher als 'MAX_IQ' sein.
	// 0: Strohdoof
	// 190: ziemlich 'intelligent'
	static const unsigned int IQ = 70;

	static const unsigned int DEAD_IQ = 170;

	// Maximale 'Intelligenz' eines Geistes
	static const unsigned int MAX_IQ = 190;

	// Geschwindigkeit eines normalen Geistes
	static const unsigned int NORMAL_SPEED = 10;

	// Geschwindigkeit eines verwundbaren Geistes
	static const unsigned int HARMLESS_SPEED = 15;

	// Geschwindigkeit eines "toten" Geistes
	static const unsigned int DEAD_SPEED = 12;


public:
	/**
	  * Geist erzeugen.
	  * @param x X-Position der Zelle des Spielfeldes, in der Geist
	  *          platziert wird.
	  * @param y Y-Position der Zelle des Spielfeldes, in der Geist
	  *          platziert wird.
	  * @param controller  Spiele-Controller, der die Aktionen
	  *                    bewertet und die Figuren steuert.
	  */
	Ghost(unsigned int x, unsigned int y, GameController* controller);

	/**
	  * Aufforderung zur Neuzeichnung.
	  * @param window     Verweis auf das Fenster, in dem die Figur
	  *                   erscheinen soll.
	  * @param cellWidth  Breite einer Zelle auf dem Spielfeld in Pixeln.
	  * @param cellHeight Hoehe einer Zelle auf dem Spielfeld in Pixeln.
	  */
	virtual void draw(Gosu::Graphics& graphics, int cellWidth, int cellHeight);

	/**
	  * Naechster Zeittakt. Die Methode muss uerberschrieben werden,
	  * um zeitgesteuerte Aktionen ausloesen zu koennen.
	  */
	virtual void nextTick();

	/**
	  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
	  * zusammen gestossen.
	  * @param otherFigure Anderer Kollisionsbeteiligter.
	  */
	virtual void handleCollisionWith(Figure* otherFigure);
};

#endif // GHOST_H
