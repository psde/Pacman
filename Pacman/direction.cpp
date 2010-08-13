//#include <stdlib.h>
#include "direction.hpp"

/**
  * Neue Richtung erzeugen.
  * @param value Neue Richtung, dabei handelt es sich
  * entweder um einen Wert aus der Aufzaehlung oder
  * um eine Bitkombination daraus.
  */
Direction::Direction(unsigned int value) {
	this->value = value;
}


/**
  * Wert der aktuellen Richtung auslesen.
  * @return Aktuelle Richtung, dabei handelt es sich
  * entweder um einen Wert aus der Aufzaehlung oder
  * um eine Bitkombination daraus.
  */
unsigned int Direction::getValue() const {
	return this->value;
}


/**
  * Eine um 180 Grad gedrehte Richtung erzeugen. Die Operation
  * ist nur definiert, wenn als Wert eine der Konstanten
  * eingetragen ist. Bei einer Kombination daraus wird
  * die unveraenderte Richtung zurueck gegeben. Der
  * Originalwert bleibt in jedem Fall unveraendert.
  * @return Neue Richtung, die um 180 Grad gedreht ist.
  */
Direction Direction::turn180Degree() const {
	switch (value) {
		case UP:    return Direction(DOWN);
		case DOWN:  return Direction(UP);
		case LEFT:  return Direction(RIGHT);
		case RIGHT: return Direction(LEFT);
	}
	// Sollte nie eintreten...
	return *this;
}
	

/**
  * Handelt es sich um eine vertikale Richtung?
  * @return <code>true</code>, wenn es sich um eine vertikale
  *         Richtung handelt.
  */
bool Direction::isVertical() const {
	return value == UP || value == DOWN;
}


/**
  * Handelt es sich um eine horizontale Richtung?
  * @return <code>true</code>, wenn es sich um eine horizontale
  *         Richtung handelt.
  */
bool Direction::isHorizontal() const {
	return value == LEFT || value == RIGHT;
}


/**
  * Vergleich zweier Richtungen.
  * @param other Zu vergleichende Richtung.
  * @return <code>true</code>, wenn beide Richtung
  *         inhaltlich gleich sind.
  */
bool Direction::operator==(Direction other) {
	return other.value == value;
}


/**
  * Vergleich der Richtungen mit dem Bitwert einer
  * anderen Richtung.
  * @param other Zu vergleichende Richtung.
  * @return <code>true</code>, wenn beide Richtung
  *         inhaltlich gleich sind.
  */
bool Direction::operator==(unsigned int other) {
	return other == value;
}


/**
  * Vergleich zweier Richtungen.
  * @param other Zu vergleichende Richtung.
  * @return <code>true</code>, wenn beide Richtung
  *         inhaltlich ungleich sind.
  */
bool Direction::operator!=(Direction& other) {
	return other.value != value;
}


/**
  * Vergleich der Richtungen mit dem Bitwert einer
  * anderen Richtung.
  * @param other Zu vergleichende Richtung.
  * @return <code>true</code>, wenn beide Richtung
  *         inhaltlich ungleich sind.
  */
bool Direction::operator!=(unsigned int other) {
	return other != value;
}


/**
  * Die Richtung mit einer anderen Zahl logisch
  * 'und' verknupefen.
  * @param other Zahl, mit der die Richtung verknuepft wird.
  * @return Neue Richtung als logisches 'Und' aus dem
  *         bisherigen Wert und der Zahl 'other'.
  */
unsigned int Direction::operator&(unsigned int other) {
	return value & other;
}


/**
  * Eine zufaellige Richtung (oben, unten, links, rechts)
  * erzeugen.
  * @return Zufaellige Richtung.
  */
Direction Direction::random() {
	return Direction(1 << rand() % 4);
}
