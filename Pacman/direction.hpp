#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>

/**
  * Die Klasse verwaltet Richtungsangaben.
  */
class Direction {
public:
	// Moegliche Bewegungsrichtung bzw. Rahmenort
	enum { NONE = 0, UP = 1, LEFT = 2, DOWN = 4, RIGHT = 8, ALL = 15 };

	// Aktuelle Bewegungsrichtung bzw. Rahmenort
	unsigned int value;

public:
	/**
	  * Neue Richtung erzeugen.
	  * @param value Neue Richtung, dabei handelt es sich
	  * entweder um einen Wert aus der Aufzaehlung oder
	  * um eine Bitkombination daraus.
	  */
	Direction(unsigned int value = NONE);

	/**
	  * Wert der aktuellen Richtung auslesen.
	  * @return Aktuelle Richtung, dabei handelt es sich
	  * entweder um einen Wert aus der Aufzaehlung oder
	  * um eine Bitkombination daraus.
	  */
	unsigned int getValue() const;

	/**
	  * Eine um 180 Grad gedrehte Richtung erzeugen. Die Operation
	  * ist nur definiert, wenn als Wert eine der Konstanten
	  * eingetragen ist. Bei einer Kombination daraus wird
	  * die unveraenderte Richtung zurueck gegeben. Der
	  * Originalwert bleibt in jedem Fall unveraendert.
	  * @return Neue Richtung, die um 180 Grad gedreht ist.
	  */
	Direction turn180Degree() const;

	/**
	  * Handelt es sich um eine vertikale Richtung?
	  * @return <code>true</code>, wenn es sich um eine vertikale
	  *         Richtung handelt.
	  */
	bool isVertical() const;

	/**
	  * Handelt es sich um eine horizontale Richtung?
	  * @return <code>true</code>, wenn es sich um eine horizontale
	  *         Richtung handelt.
	  */
	bool isHorizontal() const;

	/**
	  * Vergleich zweier Richtungen.
	  * @param other Zu vergleichende Richtung.
	  * @return <code>true</code>, wenn beide Richtung
	  *         inhaltlich gleich sind.
	  */
	bool operator==(Direction other);

	/**
	  * Vergleich der Richtungen mit dem Bitwert einer
	  * anderen Richtung.
	  * @param other Zu vergleichende Richtung.
	  * @return <code>true</code>, wenn beide Richtung
	  *         inhaltlich gleich sind.
	  */
	bool operator==(unsigned int other);

	/**
	  * Vergleich zweier Richtungen.
	  * @param other Zu vergleichende Richtung.
	  * @return <code>true</code>, wenn beide Richtung
	  *         inhaltlich ungleich sind.
	  */
	bool operator!=(Direction& other);

	/**
	  * Vergleich der Richtungen mit dem Bitwert einer
	  * anderen Richtung.
	  * @param other Zu vergleichende Richtung.
	  * @return <code>true</code>, wenn beide Richtung
	  *         inhaltlich ungleich sind.
	  */
	bool operator!=(unsigned int other);

	/**
	  * Die Richtung mit einer anderen Zahl logisch
	  * 'und' verknupefen.
	  * @param other Zahl, mit der die Richtung verknuepft wird.
	  * @return Neue Richtung als logisches 'Und' aus dem
	  *         bisherigen Wert und der Zahl 'other'.
	  */
	unsigned int  operator&(unsigned int other);

	/**
	  * Eine zufaellige Richtung (oben, unten, links, rechts)
	  * erzeugen.
	  * @return Zufaellige Richtung.
	  */
	static Direction random();
};


#endif // DIRECTION_H
