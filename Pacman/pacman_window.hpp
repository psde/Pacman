#ifndef PACMANWINDOW_H
#define PACMANWINDOW_H

#include <Gosu/Gosu.hpp>
#include "field.hpp"
#include "game_controller.hpp"

class PacmanWindow : public Gosu::Window
{
	Field* field;

	Gosu::Font font;

	void update();
	void draw();
	void buttonDown(Gosu::Button button);

	int count;

public:
	PacmanWindow();
	~PacmanWindow();

	/**
	  * Test, ob das Spiel beendet ist. Ist das der Fall,
	  * dann wird ein kleiner Hinweisdialog angezeigt.
	  */
	void checkGameOver();

};

#endif // PACMANWINDOW_H
