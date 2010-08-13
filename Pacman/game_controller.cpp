#include "cherry.hpp"
#include "pill.hpp"
#include "direction.hpp"
#include "field.hpp"
#include "game_controller.hpp"
#include "ghost.hpp"
#include "pacman.hpp"

/**
  * Einen neuen Spielecontroller erzeugen.
  * @param field Zeiger auf das Spielfeld mit den Figuren.
  */
GameController::GameController(Field* field) {
	this->field = field;
	this->points = 0;
	this->lives = 3;
	reset();
}

/**
  * Schoen sauber aufraeumen...
  */
GameController::~GameController() {
	reset();
}

void GameController::reset()
{
	this->ghostStateHarmless = false;
	this->setState(Starting);

	while(figures.size() > 0) {
		Figure* figure = figures.back();
		figures.pop_back();
		delete figure;
	}
}

/**
  * Eine neue Figur zum Controller hinzufuegen. Ab diesem Zeitpunkt
  * 'gehoert' die Figure dem Controller. Er ist also auch fuer das
  * Loeschen per 'delete' verantwortlich. Besser waeren Smart-Pointer.
  * Diese wurden aber in der Vorlesung nicht ausfuehrlich vorgestellt.
  * @param figure Neue Figur.
  */
void GameController::addFigure(Figure *figure) {
	figures.push_back(figure);
}


/**
  * Anzahl Essenspotionen im Spielfeld uebergeben.
  * @param foodCount Anzahl Essensportionen.
  */
void GameController::setFoodCount(unsigned int foodCount) {
	this->foodCount = foodCount;
}


/**
  * Referenz auf alle Figuren inkl. Pacman auslesen.
  * @return Referenz auf einen Vektor mit allen Figuren.
  */
std::vector<Figure*>& GameController::getFigures() {
	return figures;
}


/**
  * Pacman am Controller anmelden. Ab diesem Zeitpunkt
  * 'gehoert' Pacman dem Controller. Er ist also auch fuer das
  * Loeschen per 'delete' verantwortlich. Besser waeren Smart-Pointer.
  * Diese wurden aber in der Vorlesung nicht ausfuehrlich vorgestellt.
  * @param pacman Zeiger auf die Pacman-Figur.
  */
void GameController::setPacman(Pacman* pacman) {
	this->pacman = pacman;
	addFigure(pacman);
}


/**
  * Sind die Geister harmlos?
  * @return <code>true</code>, falls sie harmlos sind.
  */
bool GameController::isGhostStateHarmless() const {
	return ghostStateHarmless;
}


/**
  * Wieviele Takte lang bleiben die Geister noch harmlos?
  * @return Verbleibende Anzahl Takte.
  */
unsigned int GameController::getGhostHarmlessTicks() const {
	return ghostHarmlessTicks;
}


/**
  * Eine Figur verschieben. Dabei werden die Zellenrahmen beachtet.
  * @param figure Die zu verschiebende Figur.
  * @param direction Richtung, in die die Figur verschoben werden soll.
  */
void GameController::move(Figure* figure, Direction& direction) {
	unsigned int x = figure->getX();
	unsigned int y = figure->getY();
	if (field->allowsBorderMovement(x, y, direction)) {
		switch (direction.getValue()) {
			case Direction::UP:    y--; break;
			case Direction::LEFT:  x--; break;
			case Direction::DOWN:  y++; break;
			case Direction::RIGHT: x++; break;
		}
	}
	// Durch einen Tunnel verlassen -> auf dem anderen Ende wieder einsetzen
	x = (x + Field::FIELD_WIDTH)  % Field::FIELD_WIDTH;
	y = (y + Field::FIELD_HEIGHT) % Field::FIELD_HEIGHT;

	figure->setX(x);
	figure->setY(y);
	figure->setDirection(direction);

	// Wenn Pacman bewegt wurde: Nachsehen, ob sich auf dem neuen
	// Feld Essen befindet.
	if (figure == pacman) {
		if (field->getCell(pacman->getX(), pacman->getY())->isFood()) {
			points += DOT_POINTS;
			foodCount--;
		}
		field->getCell(pacman->getX(), pacman->getY())->setFood(false);
	}
}


/**
  * Ermittelt die Richtung, in die sich eine Figure bewegen muss,
  * wenn sie Pacman treffen möchte. Es wird dabei immer 
  * angestrebt, die Figur abwechselnd horizontal und vertikal 
  * zu bewegen.
  * @param figure Zu bewegende Figure.
  * @param figureCurrentDirection Aktuelle Bewegungsrichtung der Figur.
  * @return Einzuschlagende Richtung.
  */
Direction GameController::getDirectionToPacman(Figure* figure, Direction figureCurrentDirection) const 
{
	return this->getDirectionToCoordinates(figure, pacman->getX(), pacman->getY(), figureCurrentDirection);
}

Direction GameController::getDirectionToCoordinates(Figure* figure, unsigned int x, unsigned int y, Direction figureCurrentDirection) const
{
	if (figureCurrentDirection.isVertical()) {
		if (x < figure->getX()) {
			return Direction::LEFT;
		}
		if (x > figure->getX()) {
			return Direction::RIGHT;
		}
	}
	else {
		if (y < figure->getY()) {
			return Direction::UP;
		}
		if (y > figure->getY()) {
			return Direction::DOWN;
		}
    }
    return figureCurrentDirection;
}

/**
  * Kann sich die Figur in die gewuenschte Richtung bewegen?
  * Befindet sich z.B. dort ein Rand?
  * @param figure Zu bewegende Figur.
  * @param direction Zielrichtung der Figur.
  * @return <code>true</code>, wenn die Bewegung moeglich ist.
  */
bool GameController::canMove(Figure* figure, Direction& direction) const {
	return field->allowsBorderMovement(figure->getX(), figure->getY(), direction);
}


/**
  * Zeitablauf: Alle Figuren bewegen.
  */
void GameController::nextTick() {
	if(this->state == Starting)
	{
		this->ticks--;
		if(this->ticks == 0)
			this->setState(Playing);
	}
	else if(this->state == LevelOver)
	{
		this->ticks--;
		if(this->ticks == 0)
		{
			if(this->field->nextLevel())
			{
				this->setState(Starting);
			}
			else
			{
				this->setState(GameOver);
			}
		}
	}
	else if(this->state == Playing)
	{
		if (ghostStateHarmless) {
			if (--ghostHarmlessTicks <= 0) {
				ghostStateHarmless = false;
			}
		}

		for (std::vector<Figure*>::iterator iter = this->figures.begin(); iter != this->figures.end(); ++iter ) {
			// Die Figur darf noch nicht tot sein.
			Figure* figure = *iter;
			if (figure->getState() != Dead) {
				figure->nextTick();
				handleCollisionWithPacman(figure);
			}
		}

		if(this->foodCount == 0)
		{
			this->setState(LevelOver);
		}

		if(pacman->getState() == Dead)
		{
			if(--this->lives == 0)
			{
				this->state = GameOver;
			}
			else
			{
				for (std::vector<Figure*>::iterator iter = this->figures.begin(); iter != this->figures.end(); ++iter ) {
					// Die Figur darf noch nicht tot sein.
					Figure* figure = *iter;
					if (figure->getState() != Dead) {
						figure->reset();
					}
				}
				pacman->reset();
				this->setState(Starting);
			}
		}
	}
}


/**
  * Eine Taste wurde gedrueckt, um die Figur in eine bestimmte
  * Richtung zu schicken. 
  * @param direction Richtung, in die die Figur(en) bewegt werden soll(en).
  */
void GameController::keyPressed(Direction direction) {
	pacman->keyPressed(direction);
	handleCollisionWithPacman(pacman);
}

	
/**
  * Auf Kollisionen untersuchen: Hat die uebergebene Figur dieselbe
  * Koordinate wie Pacman? Dann wird bei dieser Figur die
  * Kollisionsbehandlung ausgeloest und Pacman uebergeben.
  * @param figure Zu untersuchende Figur.
  */
void GameController::handleCollisionWithPacman(Figure* figure) {
	// Wurde eine andere Figur als Pacman bewegt?
	if (figure != pacman) {
		if (pacman->isCollisionWith(figure)) {
			figure->handleCollisionWith(pacman);
		}
	}
	// Pacman wurde bewegt.
	else {
		for (std::vector<Figure*>::iterator iter = this->figures.begin(); iter != this->figures.end(); ++iter ) {
			Figure* figure = (*iter);
			if ((figure != pacman) && figure->getState() == Alive) {
				handleCollisionWithPacman(figure);
			}
		}
	}
}


/**
  * Ein Geist ist mit Pacman kollidiert. Daraufhin
  * soll Pacman als tot markiert werden, wenn der
  * Geist gefaehrlich ist. Andernfalls wird der
  * Geist vernichtet.
  */
void GameController::collisionOfPacmanWith(Ghost* ghost) {
	if(ghost->getState() != Alive) return;

	if (ghostStateHarmless) {
		ghost->setState(Dying);
		points += DEAD_GHOST_POINTS;
	}
	else {
		pacman->setState(Dying);
	}
}


/**
  * Pacman ist mit einer Pille kollidiert. Damit
  * werden alle Geister fuer eine Zeit harmlos. Die
  * Pille wird geloescht.
  * @param pill Pille, mit der Pacman kollidiert ist.
  */
void GameController::collisionOfPacmanWith(Pill* pill) {
	points += PILL_POINTS;
	ghostStateHarmless = true;
	ghostHarmlessTicks = GHOSTS_HARMLESS_TICKS;
	pill->setState(Dead);
}

/**
  * Pacman ist mit einer Kirsche kollidiert. Der
  * Spieler bekommt Bonuspunkte. Die
  * Kirsche wird geloescht.
  * @param cherry Kirsche, mit der Pacman kollidiert ist.
  */
void GameController::collisionOfPacmanWith(Cherry* cherry) {
	points += CHERRY_POINTS;
	cherry->setState(Dead);
}

/**
  * Aktuelle Punktezahl auslesen.
  * @return Aktuelle Punktezahl.
  */
unsigned int GameController::getPoints() const {
	return points;
}


/**
  * Ist das Spiel zuende? Es ist dann vorueber, wenn
  * entweder Pacman tot ist oder aber das ganze
  * Essen aufgegessen wurde.
  * @return <code>true</code>, wenn das Spiel zuende ist.
  */
/*bool GameController::isGameOver() const {
	return pacman->isDead() || foodCount == 0;
}*/
void GameController::setState(GameState state)
{
	this->state = state;
	if(this->state == Starting) 
		this->ticks = STARTING_TICKS;

	if(this->state == LevelOver)
		this->ticks = LEVELCHANGE_TICKS;
}

GameState GameController::getState()
{
	return this->state;
}

unsigned int GameController::getLives()
{
	return this->lives;
}

/**
  * Ist Pacman tot?
  * @return <code>true</code>, wenn Pacman tot ist.
  */
/*bool GameController::isPacmanDead() const {
	return pacman->isDead();
}
*/