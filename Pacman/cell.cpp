#include "cell.hpp"

/**
  * Eine neue Zelle erzeugen (ohne Essen, ohne Rahmen und Ausgang)
  */
Cell::Cell() 
{
	reset();
}

void Cell::reset()
{
	food = false;
	exit = false;
	prisonExit = false;
	border = Direction::NONE;
}

/**
  * Aufforderung zur Neuzeichnung.
  * @param window     Verweis auf das Fenster, in dem die Zelle
  *                   erscheinen soll.
  * @param x X-Koordinate in Pixeln der Zelle.
  * @param y Y-Koordinate in Pixeln der Zelle.
  * @param w Breite der Zelle in Pixeln.
  * @param h Hoehe der Zelle in Pixeln.
  */
void Cell::draw(Gosu::Graphics& graphics, int x, int y, int w, int h) {
	Gosu::Color borderColor(0, 0, 230);

	// Hat die Zelle oben einen Rand?
	if (border & Direction::UP) {
		graphics.drawLine(x + 1, y + 1, borderColor, x + w + 1, y + 1, borderColor, 2);
	}
	// Hat die Zelle links einen Rand?
	if (border & Direction::LEFT) {
		graphics.drawLine(x + 1, y + 1, borderColor, x + 1, y + h + 2, borderColor, 2);
	}
	// Hat die Zelle unten einen Rand?
	if (border & Direction::DOWN) {
		graphics.drawLine(x + 1, y + h + 1, borderColor, x + w + 1, y + h + 1, borderColor, 2);
	}
	// Hat die Zelle rechts einen Rand?
	if (border & Direction::RIGHT) {
		graphics.drawLine(x + w + 1, y + 1, borderColor, x + w + 1, y + h + 1, borderColor, 2);
	}

	if(food)
	{
		unsigned int innerX = x + 4;
		unsigned int innerY = y + 2;
		unsigned int innerW = w - 8;
		unsigned int innerH = h - 4;

		unsigned int foodSize = int(innerW * 0.2);
		unsigned int centerX = int((innerW - foodSize) / 2 + innerX);
		unsigned int centerY = int((innerH - foodSize) / 2 + innerY);

		Gosu::Color foodColor(255, 184, 151);

		graphics.drawQuad(centerX, centerY, foodColor, 
						  centerX + foodSize, centerY, foodColor,
						  centerX, centerY + foodSize, foodColor,
						  centerX + foodSize, centerY + foodSize, foodColor, 3);
	}

	if(prisonExit)
	{
		graphics.drawLine(x + 1, y + h/2 + 1, Gosu::Colors::yellow, x + w + 1, y + h/2 + 1, Gosu::Colors::yellow, 2);
	}
}


/**
  * Hat die Zelle aus in der gewuenschten Richtung
  * einen Rand? Der Ausgang (<code>exit</code> ist
  * <code>true</code>) wird dabei nicht beruecksichtigt.
  * Wird kein Parameter uebergeben, dann wird geprueft,
  * ob die Zelle ueberhaupt einen Rand besitzt.
  * @param dir Gewuenschte Richtung.
  * @return <code>true</code>: Ja, es ist ein Rand vorhanden.
  */
bool Cell::isBorder(Direction dir) const {
	return (dir & border) != 0;
}


/**
  * Die Zelle bekommt Essen eingetragen oder geloescht.
  * @param food <code>true</code>, wenn die Zelle Essen
  *             eingetragen bekommt.
  */
void Cell::setFood(bool food) {
	this->food = food;
}


/**
  * Abfrage, ob innerhalb der Zelle Essen eingetragen ist.
  * @return <code>true</code>, wenn Essen vorhanden ist.
  */
bool Cell::isFood() const {
	return food;
}


/**
  * Die Zelle bekommt einen Ausgang eingetragen oder entfernt.
  * @param exit <code>true</code>, wenn die Zelle einen Ausgang
  *             eingetragen bekommt.
  */
void Cell::setExit(bool exit) {
	this->exit = exit;
}


/**
  * Abfrage, ob innerhalb der Zelle ein Ausgang eingetragen ist.
  * @return <code>true</code>, wenn ein Ausgang vorhanden ist.
  */
bool Cell::isExit() const {
	return exit;
}


void Cell::setPrisonExit(bool prisonexit)
{
	this->prisonExit = prisonexit;
}

bool Cell::isPrisonExit() const
{
	return this->prisonExit;
}


/**
  * Einen neuen Rahmen eintragen. Der Rahmen 'border' ist
  * eine Bitkombination der Konstanten der Klasse 
  * 'Direction'.
  * @param border Neuer Rahmen als Bitkombination der Konstanten
  *               der Klasse 'Direction'.
  */
void Cell::setBorder(unsigned int border) {
	this->border = border;
}


/**
  * Rahmen an einer oder mehreren Seiten ergaenzen.
  * @param border Seite(n) mit zusaetzlichem Rahmen.
  */
void Cell::addBorder(unsigned int border) {
	this->border |= border;
}


/**
  * Rahmen an einer oder mehreren Seiten ergaenzen.
  * @param border Seite(n) mit zusaetzlichem Rahmen.
  */
void Cell::removeBorder(unsigned int border) {
	this->border &= ~border;
}
