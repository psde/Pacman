#ifndef PACMAN_H
#define PACMAN_H

#include <Gosu/Gosu.hpp>
#include <vector>
#include "figure.hpp"

struct PacmanDescriptor {
	BoundingBox circle;
};

class Pacman: public Figure {

	// Schliesswinkel des Mundes
	static const unsigned int MIN_MOUTH_ANGLE = 0;

	// Oeffnungswinkel des Mundes
	static const unsigned int MAX_MOUTH_ANGLE = 60;

	// Schrittweite in Grad, mit der der Mund
	// geoeffnet oder geschlossen werden soll.
	static const unsigned int MOUTH_STEP = 10;

	// Oeffnungswinkel des Mundes.
	unsigned int mouthOpenAngle;

	// Oeffnet (Wert <code>true</code>) oder schliesst
	// (Wert <code>false</code>) sich der Mund gerade.
	bool mouthOpening;


	// Geschwindigkeit des Pacman
	static const unsigned int NORMAL_SPEED = 5;

	// Richtung, in der Pacman gerade läuft
	Direction direction;

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
	unsigned int getAngleFromDirection() const;

public:
	/**
	  * Pacman erzeugen.
	  * @param x X-Position der Zelle des Spielfeldes, in der Pacman
	  *          platziert wird.
	  * @param y Y-Position der Zelle des Spielfeldes, in der Pacman
	  *          platziert wird.
	  * @param controller  Spiele-Controller, der die Aktionen
	  *                    bewertet und die Figuren steuert.
	  */
	Pacman(unsigned int x, unsigned int y, GameController* controller);

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
	  * Eine Taste wurde gedrueckt, um die Figur in eine bestimmte
	  * Richtung zu schicken. 
	  * @param direction Richtung, in die die Figur(en) bewegt werden soll(en).
	  */
	void keyPressed(Direction direction);

	/**
	  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
	  * zusammen gestossen.
	  * @param otherFigure Anderer Kollisionsbeteiligter.
	  */
	virtual void handleCollisionWith(Figure* otherFigure);

	void reset();
};

#endif // PACMAN_H
