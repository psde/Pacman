#include "field.hpp"
#include "ghost.hpp"
#include "pacman.hpp"
#include "cherry.hpp"
#include "pill.hpp"
#include "game_controller.hpp"

#include <iostream>
#include <GL/glew.h>

static const unsigned int NUM_LEVELS = 3;
/**
  * Quelle, aus der das Spielfeld aufgebaut wird.
  * Legende:
  * <ul>
  *   <li> ' ' = freies Feld</li>
  *   <li> '*' = Stein</li>
  *   <li> 'P' = Pacman</li>
  *   <li> '0' - '3': Geist</li>
  *   <li> 'C' = Kirsche (Bonuspunkte)</li>
  *   <li> 'o' = Ernergiepille</li>
  *   <li> '#' = Gefaengnis</li>
  *   <li> 'E' = Tunnel auf die andere Seite des Spielfeldes</li>
  *   <li> '.' = Punkt</li>
  *   <li> '-' = Gefaengnisausgang -> wird ignoriert</li>
  *  </ul>
  */
std::string fieldLayout[NUM_LEVELS] = {
    ".....*.........*....."
    "o***.*.*******.*.***o"
    "..........C.........."
    "**.*.****.*.****.*.**"
    " *.*.*....*.*....*.* "
    "**.*.****.*.****.*.**"
    "E .*......*......*. E"
    "**.*** ******* ***.**"
    " *.               .* "
    " *.*** ###-### ***.* "
    " *.*   #01 23#   *.* "
    "**.* * ###-### * *.**"
    "E .  *         *  . E"
    "**.****** * ******.**"
    ".*.....   *   .....*."
    ".*.***.*******.***.*."
    "..........P.........."
    ".***.****.*.****.***."
    ".*.*.*....*....*.*.*."
    "o*.*.*.*******.*.*.*o"
    ".....................",

    "....................."
    ".*****.*******.*****."
    "o*   *.*.....*.*   *o"
    ".*****.*.*.*.*.*****."
    ".......*.*.*.*......."
    "****.*.*..C..*.*.****"
    " *...*...*.*...*...* "
    " *.***** *.* *****.* "
    "**...*         *...**"
    "E  *.* ###-### *.*  E"
    "****.  #01 23#  .****"
    "E  *.* ###-### *.*  E"
    "**...*         *...**"
    " *.*.*** * * ***.*.* "
    " *.*.....* *.....*.* "
    "**.*** *.* *.* ***.**"
    ".......*..P..*......."
    ".*** * ******* * ***."
    "o*...*    C    *...*o"
    ".*.******.*.******.*."
    "..........*..........",

    "          .          "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "       ###-###       "
    "       #01 23#       "
    "       ###-###       "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "                     "
    "          P          "
};


/**
  * Ein neues Spielfeld erzeugen.
  */
Field::Field(/*Gosu::Graphics& graphics*/) {
	this->levelNumber = 1;
	this->cellHeight = 28;
	this->cellWidth = this->cellHeight;
	this->controller = new GameController(this);

	setup(this->levelNumber);
}

/**
  * Aufraeumarbeiten.
  */
Field::~Field() {
	delete controller;
}

/**
  * Initialisierung des Spielfeldes aus einer textuellen Beschreibung.
  * @param buf Aufbau des Spielfeldes (siehe Erlaeuterung oben).
  */
void Field::setup(unsigned int levelNumber) {
	controller->reset();
	std::string buf = fieldLayout[levelNumber-1];
    unsigned int foodCount = 0;
    for (unsigned int index = 0; buf[index] != 0 && index < FIELD_WIDTH * FIELD_HEIGHT; index++) {
		unsigned int x = index % FIELD_WIDTH;
		unsigned int y = index / FIELD_WIDTH;

		cells[x][y].reset();

        switch (buf[index]) {
			case '*': 
			case '#':	cells[ x ][ y ].setBorder(Direction::RIGHT | Direction::DOWN);
						// Gemeinsamen Innenbereich zusammenlegen

						// Hat die linke Nachbarzelle einen rechten Rand?
						if (x > 0 && cells[ x - 1 ][ y ].isBorder(Direction::RIGHT)) {
							// Ja: Rechts bei rechter Zelle entfernen
							cells[ x - 1 ][ y ].removeBorder(Direction::RIGHT);
						}
						else {
							// Nein: Links und rechts bei eigener Zelle setzen
							cells[ x ][ y ].addBorder(Direction::LEFT);
						}

						// Hat die obere Nachbarzelle einen unteren Rand?
						if (y > 0 && cells[ x ][ y - 1 ].isBorder(Direction::DOWN)) {
							// Ja: Unten bei obere Zelle entfernen
							cells[ x ][ y - 1 ].removeBorder(Direction::DOWN);
						}
						else {
							// Nein: oben bei eigener Zelle setzen
							cells[ x ][ y ].addBorder(Direction::UP);
						}

						break;
			case '.':	cells[ x ][ y ].setFood(true);
						foodCount++;
						break;			
			case '-':	cells[ x ][ y ].setPrisonExit(true);
						break;
			case 'E':	cells[ x ][ y ].setExit(true);
						break;
			case 'P':	controller->setPacman(new Pacman(x, y, controller));
						break;
			case 'C':	controller->addFigure(new Cherry(x, y, controller));
						break;
			case 'o':	controller->addFigure(new Pill(x, y, controller));
						break;
            default :	if (buf[index] >= '0' && buf[index] <= '3') {
						   controller->addFigure(new Ghost(x, y, controller));
						}
		}

		// Bei Aussenzellen, die kein Ausgang sind, muessen
		// Rahmen gesetzt werden.
		if ((x == 0) && !cells[ x ][ y ].isExit()) {
			cells[ x ][ y ].addBorder(Direction::LEFT);
		}
		if ((x == FIELD_WIDTH - 1) && !cells[ x ][ y ].isExit()) {
			cells[ x ][ y ].addBorder(Direction::RIGHT);
		}
		if ((y == 0) && !cells[ x ][ y ].isExit()) {
			cells[ x ][ y ].addBorder(Direction::UP);
		}
		if ((y == FIELD_HEIGHT - 1) && !cells[ x ][ y ].isExit()) {
			cells[ x ][ y ].addBorder(Direction::DOWN);
		}
    }
	controller->setFoodCount(foodCount);
}

/**
  * Wird aufgerufen, wenn das Spielfeld neu
  * gezeichnet werden muss.
  * Die Methode ueberschreibt eine Methode der Basisklasse.
  * @param event Informationen ueber das Ereignis, das das
  *              Neuzeichnen ausgeloest hat.
  * @return <code>true</code>, wenn das Eriegnis 'verbraucht' wurde.
  */
/*void Field::paintEvent(QPaintEvent* event) {
	cellWidth  = width()  / FIELD_WIDTH;
	cellHeight = height() / FIELD_HEIGHT;

	// Alle Zellen neuzeichnen.
	for (unsigned int xcount = 0; xcount < FIELD_WIDTH; ++xcount) {
		for (unsigned int ycount = 0; ycount < FIELD_HEIGHT; ++ycount) {
			cells[ xcount ][ ycount ].paint(this,
											xcount * cellWidth,
											ycount * cellHeight,
											cellWidth, cellHeight);
		}
	}

	// Alle Figuren neuzeichnen, die nicht tot sind.
	for (QVectorIterator<Figure*> iter(controller->getFigures()); iter.hasNext();) {
		Figure* figure = iter.next();
		if (!figure->isDead()) {
			figure->paint(this, cellWidth, cellHeight);
		}
	}
}*/

void Field::draw(Gosu::Graphics& graphics) {
	glLoadIdentity();
	glTranslatef(5.0f, 5.0f, 0.0f);

	for (unsigned int xcount = 0; xcount < FIELD_WIDTH; ++xcount) {
		for (unsigned int ycount = 0; ycount < FIELD_HEIGHT; ++ycount) {
			cells[ xcount ][ ycount ].draw(graphics,
											xcount * cellWidth,
											ycount * cellHeight,
											cellWidth, cellHeight);
		}
	}

	for (std::vector<Figure*>::iterator iter = controller->getFigures().begin(); iter != controller->getFigures().end(); ++iter) {
		Figure* figure = (*iter);
		if (figure->getState() != Dead) {
			figure->draw(graphics, cellWidth, cellHeight);
		}
	}
}


/**
  * Liest die Zelle aus, die sich an der Koordinate (x,y)
  * im Spielfeld befindet.
  * @param x X-Koordinate der Zelle
  * @param y Y-Koordinate der Zelle
  * @return Zeiger auf die Zelle.
  */
Cell* Field::getCell(unsigned int x, unsigned int y) {
	return &cells[ x ][ y ];
}


/**
  * Kann sich eine Figur, die sich auf der Zelle an Position (x, y) befindet,
  * in die angegebene Richtung bewegen? Ist also dort kein Rahmen vorhanden?
  * @param x         X-Position der Zelle, von der aus die Richtung untersucht werden soll.
  * @param y         Y-Position der Zelle, von der aus die Richtung untersucht werden soll.
  * @param direction Richtung, in die gelaufen werden soll.
  * @return <code>true</code> Es kann gelaufen werden, da sich keine
  *         Barriere im Weg befindet.
  *         <code>false</code> In der Richtung befindet sich eine Barriere.
  */
bool Field::allowsBorderMovement(unsigned int x, unsigned int y, Direction direction) const {
	// Die Zelle hat einen Rand in der Richtung
	if (cells[ x ][ y ].isBorder(direction)) {
		return false;
	}

	if (direction == Direction::RIGHT) {
		// Geht es rechts noch weiter?
		if ((x < FIELD_WIDTH - 1) && !cells[ x + 1 ][ y ].isBorder(Direction::LEFT)) {
			return true;
		}
		// Gibt es einen Ausgang (Tunnel) nach rechts?
		if ((x == FIELD_WIDTH - 1) && cells[ x ][ y ].isExit()) {
			return true;
		}
	}
	else if (direction == Direction::LEFT) {
		// Geht es links noch weiter?
		if ((x > 0) && !cells[ x - 1 ][ y ].isBorder(Direction::RIGHT)) {
			return true;
		}
		// Gibt es einen Ausgang (Tunnel) nach links?
		if ((x == 0) && cells[ x ][ y ].isExit()) {
			return true;
		}
	}
	else if (direction == Direction::UP) {
		// Geht es oben noch weiter?
		if ((y > 0) && !cells[ x ][ y - 1 ].isBorder(Direction::DOWN)) {
			return true;
		}
		// Gibt es einen Ausgang (Tunnel) nach oben?
		if ((y == 0) && cells[ x ][ y ].isExit()) {
			return true;
		}
	}
	else if (direction == Direction::DOWN) {
		// Geht es unten noch weiter?
		if ((y < FIELD_HEIGHT - 1) && !cells[ x ][ y + 1 ].isBorder(Direction::UP)) {
			return true;
		}
		// Gibt es einen Ausgang (Tunnel) nach unten?
		if ((y == FIELD_HEIGHT - 1) && cells[ x ][ y ].isExit()) {
			return true;
		}
	}

	return false;
}


/**
  * Die Methode wird zyklisch in festen Zeitabstaenden
  * aufgerufen. 
  */
void Field::nextTick() {
	// Aufruf an den Controller deligieren.
	controller->nextTick();

	//update();
}


/**
  * Eine Taste wurde gedrueckt, um die Figur in eine bestimmte
  * Richtung zu schicken. 
  * @param direction Richtung, in die die Figur(en) bewegt werden soll(en).
  */
void Field::keyPressed(Direction direction) {
	// Aufruf an den Controller deligieren.
	controller->keyPressed(direction);
	//update();
}

	
/**
  * Aktuelle Punktezahl auslesen.
  * @return Aktuelle Punktezahl.
  */
unsigned int Field::getPoints() const {
	return controller->getPoints();
}


/**
  * Ist das Spiel zuende? Es ist dann vorueber, wenn
  * entweder Pacman tot ist oder aber das ganze
  * Essen aufgegessen wurde.
  * @return <code>true</code>, wenn das Spiel zuende ist.
  */
/*bool Field::isGameOver() const {
	return controller->isGameOver();
}*/

GameState Field::getState()
{
	return this->controller->getState();
}

unsigned int Field::getLevelNumber()
{
	return levelNumber;
}

unsigned int Field::getMaxLevels()
{
	return NUM_LEVELS;
}

unsigned int Field::getLives()
{
	return this->controller->getLives();
}

bool Field::nextLevel()
{
	levelNumber++;
	if(levelNumber > NUM_LEVELS)
	{
		return false;
	}
	else
	{
		setup(levelNumber);
		return true;
	}
}

/**
  * Ist Pacman tot?
  * @return <code>true</code>, wenn Pacman tot ist.
  */
/*bool Field::isPacmanDead() const {
	return controller->isPacmanDead();
}*/

/*QSize Field::sizeHint () const {
	return QSize(700, 700);
}*/
