#ifndef FIELD_H
#define FIELD_H

#include <Gosu/Gosu.hpp>
#include "cell.hpp" 

class Pacman;
class GameController;
enum GameState;

class Field {
public:

	// Anzahl Zellen in der Breite
	static const unsigned int FIELD_WIDTH  = 21;
	// Anzahl Zellen in der Hoehe
	static const unsigned int FIELD_HEIGHT = 21;

private:

	// Array mit den Zellen selbst
	Cell cells[FIELD_WIDTH][FIELD_HEIGHT];

	// Die Klasse GameController beinhaltet fast die
	// komplette Logik der Spielsteuerung.
	GameController* controller;

	// Aktuelles level
	unsigned int levelNumber;

	// Breite einer Zelle in Pixeln
	unsigned int cellWidth;

	// Hoehe einer Zelle in Pixeln
	unsigned int cellHeight;

	/**
	  * Initialisierung des Spielfeldes aus einer textuellen Beschreibung.
	  * @param levelNumber Nummer des Levels (siehe Erlaeuterung oben).
	  */
	void setup(unsigned int levelNumber);

public:
	/**
	  * Ein neues Spielfeld erzeugen.
	  */
	Field();

	/**
	  * Aufraeumarbeiten.
	  */
	virtual ~Field();

	/**
	  * Die Methode wird zyklisch in festen Zeitabstaenden
	  * aufgerufen. 
	  */
	void nextTick();

	/**
	  * Eine Taste wurde gedrueckt, um die Figur in eine bestimmte
	  * Richtung zu schicken. 
	  * @param direction Richtung, in die die Figur(en) bewegt werden soll(en).
	  */
	void keyPressed(Direction direction);

	/**
	  * Kann eine Figur, die sich in der Zelle an der Koordinate
	  * (x,y) befindet, in die Richtung 'direction' gehen oder
	  * ist dort ein Rahmen?
	  * @param x X-Position der Zelle und damit auch der Figur
	  * @param y Y-Position der Zelle und damit auch der Figur
	  * @param direction Richtung, in die die Figur gehen moechte.
	  * @return <code>true</code>, wenn eine Bewegung moeglich ist oder
	  *         <code>false</code>, falls ein Rahmen im Weg ist.
	  */
	bool allowsBorderMovement(unsigned int x, unsigned int y, Direction direction) const;

	/**
	  * Liest die Zelle aus, die sich an der Koordinate (x,y)
	  * im Spielfeld befindet.
	  * @param x X-Koordinate der Zelle
	  * @param y Y-Koordinate der Zelle
	  * @return Zeiger auf die Zelle.
	  */
	Cell* getCell(unsigned int x, unsigned int y);

	/**
	  * Wird aufgerufen, wenn das Spielfeld neu
	  * gezeichnet werden muss.
	  * Die Methode ueberschreibt eine Methode der Basisklasse.
	  * @param event Informationen ueber das Ereignis, das das
	  *              Neuzeichnen ausgeloest hat.
	  * @return <code>true</code>, wenn das Eriegnis 'verbraucht' wurde.
	  */
	//virtual void paintEvent(QPaintEvent* event);
	virtual void draw(Gosu::Graphics& graphics);

	/**
	  * Aktuelle Punktezahl auslesen.
	  * @return Aktuelle Punktezahl.
	  */
	unsigned int getPoints() const;

	/**
	  * Ist das Spiel zuende? Es ist dann vorueber, wenn
	  * entweder Pacman tot ist oder aber das ganze
	  * Essen aufgegessen wurde.
	  * @return <code>true</code>, wenn das Spiel zuende ist.
	  */
	//bool isGameOver() const;

	GameState getState();

	unsigned int getLevelNumber();
	unsigned int getMaxLevels();

	unsigned int getLives();

	bool nextLevel();

	/**
	  * Ist Pacman tot?
	  * @return <code>true</code>, wenn Pacman tot ist.
	  */
	//bool isPacmanDead() const;

	//virtual QSize sizeHint () const;
};

#endif // FIELD_H
