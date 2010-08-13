#include "figure.hpp"
#include <GL/glew.h>

/**
  * Eine Figur erzeugen.
  * @param x X-Position der Zelle des Spielfeldes, in der die Figur
  *          platziert wird.
  * @param y Y-Position der Zelle des Spielfeldes, in der die Figur
  *          platziert wird.
  * @param controller  Spiele-Controller, der die Aktionen
  *                    bewertet und die Figuren steuert.
  */
Figure::Figure(unsigned int x, unsigned int y, GameController* controller) {
	this->cellX = x;
	this->cellY = y;
	this->startx = x;
	this->starty = y;
	this->controller = controller;
	this->state = Alive;
	this->ticks = 0;
}


/**
  * Liefert die relative X-Koordinate innerhalb der Zelle zurueck,
  * an der die Figur gezeichnet wird. Der freie Rand um die Figur
  * wird beruecksichtigt.
  * @param cellWidth Breite der Zelle in Pixeln.
  * @return Relative X-Koordinate innerhalb der Zelle als Ursprung der Figur.
  */
unsigned int Figure::getInnerX(unsigned int cellWidth) const {
	return cellWidth * getX() + EMPTY_BORDER;
}


/**
  * Liefert die relative Y-Koordinate innerhalb der Zelle zurueck,
  * an der die Figur gezeichnet wird. Der freie Rand um die Figur
  * wird beruecksichtigt.
  * @param cellHeight Hoehe der Zelle in Pixeln.
  * @return Relative Y-Koordinate innerhalb der Zelle als Ursprung der Figur.
  */
unsigned int Figure::getInnerY(unsigned int cellHeight) const {
	return cellHeight * getY() + EMPTY_BORDER;
}


/**
  * Liefert die Breite fuer die Figur zurueck. Diese entspricht der
  * Zellenbreite abzueglich des freien Randes.
  * @param cellWidth Breite der Zelle in Pixeln.
  * @return Breite, die fuer die Figur zur Verfuegung steht.
  */
unsigned int Figure::getInnerW(unsigned int cellWidth) const {
	return 1 * cellWidth - 2 * EMPTY_BORDER;
}


/**
  * Liefert die Hoehe fuer die Figur zurueck. Diese entspricht der
  * Zellenhoehe abzueglich des freien Randes.
  * @param cellHeight Hoehe der Zelle in Pixeln.
  * @return Hoehe, die fuer die Figur zur Verfuegung steht.
  */
unsigned int Figure::getInnerH(unsigned int cellHeight) const {
	return 1 * cellHeight - 2 * EMPTY_BORDER;
}


/**
  * Ermittelt die X-Koordinate der Figur auf dem Spielfeld.
  * @return X-Koordinate der Figur auf dem Spielfeld.
  */
unsigned int Figure::getX() const {
	return cellX;
}


/**
  * Ermittelt die Y-Koordinate der Figur auf dem Spielfeld.
  * @return Y-Koordinate der Figur auf dem Spielfeld.
  */
unsigned int Figure::getY() const {
	return cellY;
}


/**
  * X-Koordinate der Figur auf dem Spielfeld eintragen.
  * @param x Neue X-Koordinate der Figur.
  */
void Figure::setX(unsigned int x) {
	cellX = x;
}


/**
  * Y-Koordinate der Figur auf dem Spielfeld eintragen.
  * @param y Neue Y-Koordinate der Figur.
  */
void Figure::setY(unsigned int y) {
	cellY = y;
}


/**
  * Richtung, in der sich die Figur bewegt, eintragen.
  * @param direction Neue Richtung der Figur.
  */
void Figure::setDirection(Direction direction) {
	this->direction = direction;
}


/**
  * Einen Kreisbogen mit relativen Koordinaten zeichnen.
  * @param painter    Painter, der die Ausgaben vornimmt.
  * @param cellWidth  Breite der Zelle in Pixel, in die gezeichnet wird.
  * @param cellHeight Hoehe der Zelle in Pixel, in die gezeichnet wird.
  * @param bounds     Bounding-Box des Kreissegmentes, das gezeichnet wird.
  * @param rad1       1. Radius des Kreissegmentes (Rotationen des Segmentes).
  * @param rad2       2. Radius des Kreissegmentes (Oeffnungswinkel des Segmentes).
  */
void Figure::drawArc(Gosu::Graphics& graphics, Gosu::Color color, int cellWidth, int cellHeight,
					 bool fill, BoundingBox bounds, int start, int length) 
{
	if(length > 360) return;

	unsigned int x = getInnerX(cellWidth) + bounds.x * cellWidth - 3; //getInnerX(cellWidth) + (unsigned int) (bounds.x * getInnerW(cellWidth) + 0.5);
	unsigned int y = getInnerY(cellHeight) + bounds.y * cellHeight - 3; //getInnerY(cellHeight) + (unsigned int) (bounds.y * getInnerH(cellHeight) + 0.5);
	unsigned int w = bounds.w * cellWidth; //(unsigned int) (bounds.w * getInnerW(cellWidth) + 0.5);
	unsigned int h = bounds.h * cellHeight; //(unsigned int) (bounds.h * getInnerH(cellHeight) + 0.5);

	//std::cout << x << " " << this->cellX << " | " << w << " " << cellWidth << " " <<  bounds.w << std::endl;

	glColor3f((float)color.red()/255, (float)color.green()/255, (float)color.blue()/255);

	if(fill)
	{
		glBegin(GL_TRIANGLE_FAN);
		//glVertex2f((float)cellWidth / 2 + this->cellX * cellWidth, (float)cellHeight / 2 + this->cellY * cellHeight);
		glVertex2f(x + w/2, y + h/2);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}

	int angle = -start;
	while(length!=0)
	{
		/*float x1 = cellWidth / 2 + this->cellX * cellWidth + cos((float)Gosu::degreesToRadians(angle)) * ((cellWidth / 2) - 2);
		float y1 = cellHeight / 2 + this->cellY * cellHeight + sin((float)Gosu::degreesToRadians(angle)) * ((cellWidth / 2) - 2);*/

		/*float x1 = cellWidth / 2 + this->cellX * cellWidth + cos((float)Gosu::degreesToRadians(angle)) * w/2;
		float y1 = cellHeight / 2 + this->cellY * cellHeight + sin((float)Gosu::degreesToRadians(angle)) * h/2;*/

		float x1 = x + w/2 + cos((float)Gosu::degreesToRadians(angle)) * w/2;
		float y1 = y + h/2 + sin((float)Gosu::degreesToRadians(angle)) * h/2;

		glVertex2f(x1, y1);

		angle--;
		length--;
	}

	glEnd();

}

/**
  * Ein Rechteck mit relativen Koordinaten zeichnen.
  * @param painter    Painter, der die Ausgaben vornimmt.
  * @param cellWidth  Breite der Zelle in Pixel, in die gezeichnet wird.
  * @param cellHeight Hoehe der Zelle in Pixel, in die gezeichnet wird.
  * @param fill       <code>true</code>, um das Rechteck zu fuellen.
  * @param bounds     Bounding-Box des Rechteckes, das gezeichnet wird.
  */
void Figure::drawRectangle(Gosu::Graphics& graphics, Gosu::Color color,
						unsigned int cellWidth, unsigned int cellHeight,
						bool fill,
						BoundingBox bounds) {

	unsigned int x = getInnerX(cellWidth) + bounds.x * cellWidth - 3;
	unsigned int y = getInnerY(cellHeight) + bounds.y * cellHeight - 3;
	unsigned int w = bounds.w * cellWidth;
	unsigned int h = bounds.h * cellHeight;

	glColor3f((float)color.red()/255, (float)color.green()/255, (float)color.blue()/255);

	if(fill)
	{
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x, y + h);
			glVertex2f(x + w, y + h);
			glVertex2f(x + w, y);
		glEnd();
	}
	else
	{
		// Do we even need/use it?
	}
}

void Figure::drawLine(Gosu::Graphics& graphics, Gosu::Color color, unsigned int cellWidth, unsigned int cellHeight,
					  int x1, int y1, int x2, int y2)
{
	unsigned int x = getInnerX(cellWidth);
	unsigned int y = getInnerY(cellHeight);

	glColor3f((float)color.red()/255, (float)color.green()/255, (float)color.blue()/255);

	glBegin(GL_LINES);
		glVertex2f(x + x1, y + y1);
		glVertex2f(x + x2, y + y2);
	glEnd();
}


/**
  * Untersucht, ob die uebergebene Figur mit dieser kollidiert.
  * Es wird also geprueft, ob sie dieselben Koordinaten besitzen.
  * @param otherFigure Figur, die auf Kollision mit dieser untersucht wird.
  * @return <code>true</code>, falls beide Figuren kollidieren.
  */
bool Figure::isCollisionWith(Figure* otherFigure) const {
	return cellX == otherFigure->getX() && cellY == otherFigure->getY();
}


/**
  * Figur in den Zustand 'tot' oder 'lebendig' versetzen.
  * @param dead Neuer Zustand, <code>true</code> steht dabei
  *             fuer 'tot'.
  */
/*void Figure::setDead(bool dead) {
	this->dead = dead;
}*/


/**
  * Test, ob die Figur tot ist oder nicht.
  * @return <code>true</code> steht fuer den Zustand 'tot'.
  */
/*bool Figure::isDead() const {
	return dead;
}*/

void Figure::setState(FigureState state)
{
	this->state = state;
}

FigureState Figure::getState()
{
	return this->state;
}

void Figure::reset()
{
	this->cellX = startx;
	this->cellY = starty;
	this->state = Alive;
}