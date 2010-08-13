#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>

class Direction;
class Pacman;
class Field;
class Cherry;
class Pill;
class Ghost;
class Figure;


enum GameState { Starting = 0, Playing, LevelOver, GameOver };

/**
  * Der Controller entscheidet in unterschiedlichen
  * Situationen darueber, ob Figuren geloescht werden,
  * ob Pacman getoetet wurde usw.
  */
class GameController {
public:
	// Ein Geist bleibt 500 Takte lang harmlos.
	static const unsigned int GHOSTS_HARMLESS_TICKS = 250;

	// Ein Essen bringt 5 Punkte.
	static const unsigned int DOT_POINTS = 5;
	// Ein gefressener Geist ergibt 100 Punkte.
	static const unsigned int DEAD_GHOST_POINTS = 100;
	// Eine gefressene Kirsche ergibt 50 Punkte.
	static const unsigned int CHERRY_POINTS = 50;
	// Eine gefressene Pille ergibt 10 Punkte.
	static const unsigned int PILL_POINTS = 10;

	static const unsigned int STARTING_TICKS = 70;

	static const unsigned int LEVELCHANGE_TICKS = 70;

private:
	// Zeiger auf das Spielfeld mit den Figuren.
	Field* field;

	// <code>true</code>, wenn alle Geister harmlos sind,
	// ansonsten <code>false</code>.
	bool ghostStateHarmless;

	// Rueckwaertslaufender Zaehler fuer die Anzahl Zeittakte,
	// die die Geister noch harmlos sind.
	unsigned int ghostHarmlessTicks;

	// Vektor mit allen Figuren (inkl. Pacman) auf dem Spielfeld.
	std::vector<Figure*> figures;

	// Zeiger auf die Pacman-Figur. Der Zeiger ist auch
	// im Vektor <code>figures</code> abgelegt.
	Pacman* pacman;

	// Aktuelle Punktzahl des Spielers.
	unsigned int points;

	// Zaehler fuer die Anzahl an Essensportionen, die noch
	// in den Zellen liegen.
	unsigned int foodCount;

	// Anzahl an "Leben" des Pacmans
	unsigned int lives;

	// Ticks, wird zum Starten bzw Levelwechselübergang verwendet
	unsigned int ticks;

	/**
	  * Auf Kollisionen untersuchen: Hat die uebergebene Figur dieselbe
	  * Koordinate wie Pacman? Dann wird bei dieser Figur die
	  * Kollisionsbehandlung ausgeloest und Pacman uebergeben.
	  * @param figure Zu untersuchende Figur.
	  */
	void handleCollisionWithPacman(Figure* figure);

	// Aktueller Zustand des Spiels
	GameState state;

	void setState(GameState state);

public:
	/**
	  * Einen neuen Spielecontroller erzeugen.
	  * @param field Zeiger auf das Spielfeld mit den Figuren.
	  */
	GameController(Field* field);

	/**
	  * Schoen sauber aufraeumen...
	  */
	~GameController();

	/**
	  * Eine neue Figur zum Controller hinzufuegen. Ab diesem Zeitpunkt
	  * 'gehoert' die Figure dem Controller. Er ist also auch fuer das
	  * Loeschen per 'delete' verantwortlich. Besser waeren Smart-Pointer.
	  * Diese wurden aber in der Vorlesung nicht ausfuehrlich vorgestellt.
	  * @param figure Neue Figur.
	  */
	void addFigure(Figure* figure);

	/**
	  * Anzahl Essenspotionen im Spielfeld uebergeben.
	  * @param foodCount Anzahl Essensportionen.
	  */
	void setFoodCount(unsigned int foodCount);

	/**
	  * Referenz auf alle Figuren inkl. Pacman auslesen.
	  * @return Referenz auf einen Vektor mit allen Figuren.
	  */
	std::vector<Figure*>& getFigures();

	/**
	  * Pacman am Controller anmelden. Ab diesem Zeitpunkt
	  * 'gehoert' Pacman dem Controller. Er ist also auch fuer das
	  * Loeschen per 'delete' verantwortlich. Besser waeren Smart-Pointer.
	  * Diese wurden aber in der Vorlesung nicht ausfuehrlich vorgestellt.
	  * @param pacman Zeiger auf die Pacman-Figur.
	  */
	void setPacman(Pacman* pacman);

	/**
	  * Sind die Geister harmlos?
	  * @return <code>true</code>, falls sie harmlos sind.
	  */
	bool isGhostStateHarmless() const;

	/**
	  * Wieviele Takte lang bleiben die Geister noch harmlos?
	  * @return Verbleibende Anzahl Takte.
	  */
	unsigned int getGhostHarmlessTicks() const;

	/**
	  * Eine Figur verschieben. Dabei werden die Zellenrahmen beachtet.
	  * @param figure Die zu verschiebende Figur.
	  * @param direction Richtung, in die die Figur verschoben werden soll.
	  */
	void move(Figure* figure, Direction& direction);

	/**
	  * Ermittelt die Richtung, in die sich eine Figure bewegen muss,
	  * wenn sie Pacman treffen möchte. Es wird dabei immer 
	  * angestrebt, die Figur abwechselnd horizontal und vertikal 
	  * zu bewegen.
	  * @param figure Zu bewegende Figure.
	  * @param figureCurrentDirection Aktuelle Bewegungsrichtung der Figur.
	  * @return Einzuschlagende Richtung.
	  */
	Direction getDirectionToPacman(Figure* figure,
								   Direction figureCurrentDirection) const;

	Direction getDirectionToCoordinates(Figure* figure, unsigned int x, unsigned int y, Direction figureCurrentDirection) const;

	/**
	  * Kann sich die Figur in die gewuenschte Richtung bewegen?
	  * Befindet sich z.B. dort ein Rand?
	  * @param figure Zu bewegende Figur.
	  * @param direction Zielrichtung der Figur.
	  * @return <code>true</code>, wenn die Bewegung moeglich ist.
	  */
	bool canMove(Figure* figure, Direction& direction) const;

	/**
	  * Zeitablauf: Alle Figuren bewegen.
	  */
	void nextTick();

	/**
	  * Eine Taste wurde gedrueckt, um die Figur in eine bestimmte
	  * Richtung zu schicken. 
	  * @param direction Richtung, in die die Figur(en) bewegt werden soll(en).
	  */
	void keyPressed(Direction direction);

	/**
	  * Ein Geist ist mit Pacman kollidiert. Daraufhin
	  * soll Pacman als tot markiert werden, wenn der
	  * Geist gefaehrlich ist. Andernfalls wird der
	  * Geist vernichtet.
	  */
	void collisionOfPacmanWith(Ghost* ghost);

	/**
	  * Pacman ist mit einer Pille kollidiert. Damit
	  * werden alle Geister fuer eine Zeit harmlos. Die
	  * Pille wird geloescht.
	  * @param pill Pille, mit der Pacman kollidiert ist.
	  */
	void collisionOfPacmanWith(Pill* pill);


	/**
	  * Pacman ist mit einer Kirsche kollidiert. Der
	  * Spieler bekommt Bonuspunkte. Die
	  * Kirsche wird geloescht.
	  * @param cherry Kirsche, mit der Pacman kollidiert ist.
	  */
	void collisionOfPacmanWith(Cherry* cherry);

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
	unsigned int getLives();
	void reset();

	/**
	  * Ist Pacman tot?
	  * @return <code>true</code>, wenn Pacman tot ist.
	  */
	//bool isPacmanDead() const;
};

#endif // GAMECONTROLLER_H