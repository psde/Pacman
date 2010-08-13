#ifndef CELL_H
#define CELL_H

#include <Gosu/Gosu.hpp>
#include "direction.hpp"

class Figure;

/**
  * Eine Zelle ist ein Element des Spielfeldes.
  */
class Cell {
	// Rahmen um die Zelle als Bitkombination der Konstanten
	// der Klasse 'Direction'.
	unsigned int  border;

	// Hat die Zelle Essen (<code>true</code>) oder
	// nicht (<code>false</code>)
	bool food;

	// Hat die Zelle einen Ausgang (<code>true</code>) oder
	// nicht (<code>false</code>)
	bool exit;

	bool prisonExit;

public:
	/**
	  * Eine neue Zelle erzeugen (ohne Essen, ohne Rahmen und Ausgang)
	  */
	Cell();

	/**
	  * Aufforderung zur Neuzeichnung.
	  * @param window     Verweis auf das Fenster, in dem die Zelle
	  *                   erscheinen soll.
	  * @param x X-Koordinate in Pixeln der Zelle.
	  * @param y Y-Koordinate in Pixeln der Zelle.
	  * @param w Breite der Zelle in Pixeln.
	  * @param h Hoehe der Zelle in Pixeln.
	  */
	virtual void draw(Gosu::Graphics& graphics, int x, int y, int w, int h);

	/**
	  * Hat die Zelle aus in der gewuenschten Richtung
	  * einen Rand? Der Ausgang (<code>exit</code> ist
	  * <code>true</code>) wird dabei nicht beruecksichtigt.
	  * Wird kein Parameter uebergeben, dann wird geprueft,
	  * ob die Zelle ueberhaupt einen Rand besitzt.
	  * @param dir Gewuenschte Richtung.
	  * @return <code>true</code>: Ja, es ist ein Rand vorhanden.
	  */
	bool isBorder(Direction dir = Direction::ALL) const;

	/**
	  * Die Zelle bekommt Essen eingetragen oder geloescht.
	  * @param food <code>true</code>, wenn die Zelle Essen
	  *             eingetragen bekommt.
	  */
	void setFood(bool food);

	/**
	  * Abfrage, ob innerhalb der Zelle Essen eingetragen ist.
	  * @return <code>true</code>, wenn Essen vorhanden ist.
	  */
	bool isFood() const;

	/**
	  * Die Zelle bekommt einen Ausgang eingetragen oder entfernt.
	  * @param exit <code>true</code>, wenn die Zelle einen Ausgang
	  *             eingetragen bekommt.
	  */
	void setExit(bool exit);

	/**
	  * Abfrage, ob innerhalb der Zelle ein Ausgang eingetragen ist.
	  * @return <code>true</code>, wenn ein Ausgang vorhanden ist.
	  */
	bool isExit() const;

	void setPrisonExit(bool prisonexit);
	bool isPrisonExit() const;

	/**
	  * Einen neuen Rahmen eintragen. Der Rahmen 'border' ist
	  * eine Bitkombination der Konstanten der Klasse 
	  * 'Direction'.
	  * @param border Neuer Rahmen als Bitkombination der Konstanten
	  *               der Klasse 'Direction'.
	  */
	void setBorder(unsigned int border);

	/**
	  * Rahmen an einer oder mehreren Seiten ergaenzen.
	  * @param border Seite(n) mit zusaetzlichem Rahmen.
	  */
	void addBorder(unsigned int border);

	/**
	  * Rahmen an einer oder mehreren Seiten ergaenzen.
	  * @param border Seite(n) mit zusaetzlichem Rahmen.
	  */
	void removeBorder(unsigned int border);

	void reset();
};

#endif // CELL_H
