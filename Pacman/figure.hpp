#ifndef FIGURE_H
#define FIGURE_H

#include <Gosu/Gosu.hpp>
#include "direction.hpp"

struct BoundingBox {
	double x;
	double y;
	double w;
	double h;
};

class Field;
class GameController;

enum FigureState { Alive = 0, Dying, Dead };

/**
  * Die Klasse Figur ist die Basisklasse fuer alle Figuren
  * auf dem Spielfeld.
  */
class Figure {
protected:
	// X-Position der Figur auf dem Spielfeld
	unsigned int    cellX;
	// Y-Position der Figur auf dem Spielfeld
	unsigned int    cellY;
	// Richtung, in die die Figur gerade laeuft.
	Direction       direction;

	// Ist die Figur tot?
	//bool			dead;

	// Spiele-Controller, der die Aktionen bewertet und die Figuren steuert.
	GameController* controller;

	// Geschwindigkeit der Figur, angegeben in Ticks
	unsigned int speed;

	// Tickcounter
	unsigned int ticks;

	// Status der Figur
	FigureState state;	
	
	// Startkoordinaten des Figur
	unsigned int startx, starty;

public:
	// Leerer Rahmen um die Figur: jeweils 4 Pixel
	static const unsigned int EMPTY_BORDER = 4;

	virtual void reset();

protected:

	/**
	  * Einen Kreisbogen mit relativen Koordinaten zeichnen.
	  * @param painter    Painter, der die Ausgaben vornimmt.
	  * @param cellWidth  Breite der Zelle in Pixel, in die gezeichnet wird.
	  * @param cellHeight Hoehe der Zelle in Pixel, in die gezeichnet wird.
	  * @param fill       <code>true</code>, um das Segment zu fuellen.
	  * @param bounds     Bounding-Box des Kreissegmentes, das gezeichnet wird.
	  * @param rad1       1. Radius des Kreissegmentes (Rotationen des Segmentes).
	  * @param rad2       2. Radius des Kreissegmentes (Oeffnungswinkel des Segmentes).
	  */
	void drawArc(Gosu::Graphics& graphics, Gosu::Color color, int cellWidth, int cellHeight,
				 bool fill, BoundingBox bounds, int start, int length);

	/*void drawArc(Gosu::Graphics& graphics,
				 unsigned int cellWidth, unsigned int cellHeight,
				 bool fill,
				 BoundingBox bounds,
				 unsigned int rad1, unsigned int rad2);*/

	/**
	  * Ein Rechteck mit relativen Koordinaten zeichnen.
	  * @param painter    Painter, der die Ausgaben vornimmt.
	  * @param cellWidth  Breite der Zelle in Pixel, in die gezeichnet wird.
	  * @param cellHeight Hoehe der Zelle in Pixel, in die gezeichnet wird.
	  * @param fill       <code>true</code>, um das Rechteck zu fuellen.
	  * @param bounds     Bounding-Box des Rechteckes, das gezeichnet wird.
	  */
	void drawRectangle(Gosu::Graphics& graphics, Gosu::Color color,
						unsigned int cellWidth, unsigned int cellHeight,
						bool fill,
						BoundingBox bounds);

	void drawLine(Gosu::Graphics& graphics, Gosu::Color color, unsigned int cellWidth, unsigned int cellHeight,
				  int x1, int y1, int x2, int y2);
	
	/**
	  * Liefert die relative X-Koordinate innerhalb der Zelle zurueck,
	  * an der die Figur gezeichnet wird. Der freie Rand um die Figur
	  * wird beruecksichtigt.
	  * @param cellWidth Breite der Zelle in Pixeln.
	  * @return Relative X-Koordinate innerhalb der Zelle als Ursprung der Figur.
	  */
	unsigned int getInnerX(unsigned int cellWidth) const;

	/**
	  * Liefert die relative Y-Koordinate innerhalb der Zelle zurueck,
	  * an der die Figur gezeichnet wird. Der freie Rand um die Figur
	  * wird beruecksichtigt.
	  * @param cellHeight Hoehe der Zelle in Pixeln.
	  * @return Relative Y-Koordinate innerhalb der Zelle als Ursprung der Figur.
	  */
	unsigned int getInnerY(unsigned int cellHeight) const;

	/**
	  * Liefert die Breite fuer die Figur zurueck. Diese entspricht der
	  * Zellenbreite abzueglich des freien Randes.
	  * @param cellWidth Breite der Zelle in Pixeln.
	  * @return Breite, die fuer die Figur zur Verfuegung steht.
	  */
	unsigned int getInnerW(unsigned int cellWidth) const;

	/**
	  * Liefert die Hoehe fuer die Figur zurueck. Diese entspricht der
	  * Zellenhoehe abzueglich des freien Randes.
	  * @param cellHeight Hoehe der Zelle in Pixeln.
	  * @return Hoehe, die fuer die Figur zur Verfuegung steht.
	  */
	unsigned int getInnerH(unsigned int cellHeight) const;

public:
	/**
	  * Eine Figur erzeugen.
	  * @param x X-Position der Zelle des Spielfeldes, in der die Figur
	  *          platziert wird.
	  * @param y Y-Position der Zelle des Spielfeldes, in der die Figur
	  *          platziert wird.
	  * @param controller  Spiele-Controller, der die Aktionen
	  *                    bewertet und die Figuren steuert.
	  */
	Figure(unsigned int x, unsigned int y, GameController* controller);

	/**
	  * Destruktor fuer die Aufraeumarbeiten. Er ist hier rein-virtuell,
	  * da ihn die Figur selbst nicht benoetigt.
	  */
	virtual ~Figure() {}

	/**
	  * Aufforderung zur Neuzeichnung.
	  * @param window     Verweis auf das Fenster, in dem die Figur
	  *                   erscheinen soll.
	  * @param cellWidth  Breite einer Zelle auf dem Spielfeld in Pixeln.
	  * @param cellHeight Hoehe einer Zelle auf dem Spielfeld in Pixeln.
	  */
	virtual void draw(Gosu::Graphics& graphics, int cellWidth, int cellHeight) = 0;

	/**
	  * Naechster Zeittakt. Die Methode muss uerberschrieben werden,
	  * um zeitgesteuerte Aktionen ausloesen zu koennen.
	  */
	virtual void nextTick() { }

	/**
	  * Ermittelt die X-Koordinate der Figur auf dem Spielfeld.
	  * @return X-Koordinate der Figur auf dem Spielfeld.
	  */
	virtual unsigned int getX() const;

	/**
	  * Ermittelt die Y-Koordinate der Figur auf dem Spielfeld.
	  * @return Y-Koordinate der Figur auf dem Spielfeld.
	  */
	virtual unsigned int getY() const;

	/**
	  * X-Koordinate der Figur auf dem Spielfeld eintragen.
	  * @param x Neue X-Koordinate der Figur.
	  */
	virtual void setX(unsigned int x);

	/**
	  * Y-Koordinate der Figur auf dem Spielfeld eintragen.
	  * @param y Neue Y-Koordinate der Figur.
	  */
	virtual void setY(unsigned int y);

	/**
	  * Richtung, in der sich die Figur bewegt, eintragen.
	  * @param direction Neue Richtung der Figur.
	  */
	virtual void setDirection(Direction direction);

	/**
	  * Untersucht, ob die uebergebene Figur mit dieser kollidiert.
	  * Es wird also geprueft, ob sie dieselben Koordinaten besitzen.
	  * @param otherFigure Figur, die auf Kollision mit dieser untersucht wird.
	  * @return <code>true</code>, falls beide Figuren kollidieren.
	  */
	virtual bool isCollisionWith(Figure* otherFigure) const;

	/**
	  * Kollisionsbehandlung: Diese Figur ist mit der uebergebenen
	  * zusammen gestossen.
	  * @param otherFigure Anderer Kollisionsbeteiligter.
	  */
	virtual void handleCollisionWith(Figure* otherFigure) = 0;
	
	/**
	  * Figur in den Zustand 'tot' oder 'lebendig' versetzen.
	  * @param dead Neuer Zustand, <code>true</code> steht dabei
	  *             fuer 'tot'.
	  */
	//virtual void setDead(bool dead);

	/**
	  * Test, ob die Figur tot ist oder nicht.
	  * @return <code>true</code> steht fuer den Zustand 'tot'.
	  */
	//virtual bool isDead() const;

	virtual void setState(FigureState state);
	virtual FigureState getState();
};

#endif // FIGURE_H
