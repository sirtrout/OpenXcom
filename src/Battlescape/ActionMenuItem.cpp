/*
 * Copyright 2010 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ActionMenuItem.h"
#include "../Interface/Text.h"
#include "../Engine/Palette.h"

namespace OpenXcom
{

/**
 * Sets up a Explosion sprite with the specified size and position.
 */
ActionMenuItem::ActionMenuItem(State *state, int id, Font *bigFont) : InteractiveSurface(270, 40, 25, 160 - (id*40)), _id(id), _highlighted(false)
{
	_txtDescription = new Text(100, 20, 16, 13);
	_txtDescription->setFonts(bigFont, 0);
	_txtDescription->setBig();
	_txtDescription->setHighContrast(true);
	_txtDescription->setColor(0);
	_txtDescription->setVisible(true);
	_txtDescription->setText(L"Undefined");

	_txtAcc = new Text(100, 20, 126, 13);
	_txtAcc->setFonts(bigFont, 0);
	_txtAcc->setBig();
	_txtAcc->setHighContrast(true);
	_txtAcc->setColor(0);
	_txtAcc->setText(L"Acc>");

	_txtTU = new Text(100, 20, 195, 13);
	_txtTU->setFonts(bigFont, 0);
	_txtTU->setBig();
	_txtTU->setHighContrast(true);
	_txtTU->setColor(0);
	_txtTU->setText(L"TUs>");
}

/**
 * Deletes the ActionMenuItem.
 */
ActionMenuItem::~ActionMenuItem()
{

}

void ActionMenuItem::setAction(BattleActionType action, std::wstring description, std::wstring accuracy, std::wstring timeunits)
{
	_action = action;
	_txtDescription->setText(description);
	_txtAcc->setText(accuracy);
	_txtTU->setText(timeunits);
	draw();
}

BattleActionType ActionMenuItem::getAction()
{
	return _action;
}

/**
 * Replaces a certain amount of colors in the surface's palette.
 * @param colors Pointer to the set of colors.
 * @param firstcolor Offset of the first color to replace.
 * @param ncolors Amount of colors to replace.
 */
void ActionMenuItem::setPalette(SDL_Color *colors, int firstcolor, int ncolors)
{
	Surface::setPalette(colors, firstcolor, ncolors);
	_txtDescription->setPalette(colors, firstcolor, ncolors);
	_txtAcc->setPalette(colors, firstcolor, ncolors);
	_txtTU->setPalette(colors, firstcolor, ncolors);
}

/**
 * Draws the bordered box.
 */
void ActionMenuItem::draw()
{
	SDL_Rect square;
	Uint8 color = 11;
	
	clear();
	
	square.x = 0;
	square.w = getWidth();

	square.y = 0;
	square.h = getHeight();

	for (int i = 0; i < 9; i++)
	{
		if (i == 8 && _highlighted)
			color -= 4;
		drawRect(&square, color);
		if (i < 3)
			color-=2;
		else
			color+=2;
		square.x++;
		square.y++;
		if (square.w >= 2)
			square.w -= 2;
		else
			square.w = 1;

		if (square.h >= 2)
			square.h -= 2;
		else
			square.h = 1;
	}

	_txtDescription->draw();
	_txtDescription->blit(this);
	_txtAcc->draw();
	_txtAcc->blit(this);
	_txtTU->draw();
	_txtTU->blit(this);
}

/// Processes a mouse hover in event.
void ActionMenuItem::mouseIn(Action *action, State *state)
{
	_highlighted = true;
	draw();
	InteractiveSurface::mouseIn(action, state);
}
/// Processes a mouse hover out event.
void ActionMenuItem::mouseOut(Action *action, State *state)
{
	_highlighted = false;
	draw();
	InteractiveSurface::mouseOut(action, state);
}


}
