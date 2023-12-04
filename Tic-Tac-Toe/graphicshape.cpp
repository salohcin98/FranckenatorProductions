// kernel.cpp

// This file includes code from the Circle library:
//   Circle - A C++ bare metal environment for Raspberry Pi
//   Copyright (C) 2014-2023  R. Stange <rsta2@o2online.de>

// Additional modifications and enhancements have been made
// by [Chase Poland, Nicholas Franck, & Eric Peasley] as part of the [Franckenator Productions] project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "graphicshape.h"
#include <circle/util.h>
#include <circle/string.h>

static unsigned g_seed;
static unsigned shapeType;

#if DEPTH == 8
static const TScreenColor Black = NORMAL_COLOR;
static const TScreenColor Gray  = HALF_COLOR;
static const TScreenColor Red   = HIGH_COLOR;
#elif DEPTH == 16
static const TScreenColor Black = COLOR16 (0,0,0);
static const TScreenColor Gray  = COLOR16 (10,10,10);
static const TScreenColor Red   = COLOR16 (31,10,10);
#elif DEPTH == 32
static const TScreenColor Black = COLOR32 (0,0,0, 255);
static const TScreenColor Gray  = COLOR32 (170,170,170, 255);
static const TScreenColor Red   = COLOR32 (255,170,170, 255);
#else
	#error Screen DEPTH must be 8, 16 or 32!
#endif

static unsigned randomNumber()
{
	g_seed = (214013*g_seed+2531011);
	return (g_seed>>16)&0x7fff;
}

// TIC-TAC_TOE CODE THINGS - CHASE
#define MIN(x, y) ((x) < (y) ? (x) : (y))
const int BOARD_SIZE = 300;


enum Mark { EMPTY, X, O};

struct BoardPosition {
	int x;
	int y;
	int size;
};

CGraphicShape::CGraphicShape (unsigned nDisplayWidth, unsigned nDisplayHeight)
:	m_nDisplayWidth (nDisplayWidth),
	m_nDisplayHeight (nDisplayHeight)
{
	m_nSpeed = 0.5f+(randomNumber() % 256)*0.1f;

	m_nAngle = (randomNumber() % 256);

	m_nType = (shapeType++)%NB_GRAPHICSHAPE;
	
	m_nParam1 = 2+(randomNumber() % 32);
	
	
	
	if(m_nType == GRAPHICSHAPE_CIRCLE || m_nType == GRAPHICSHAPE_CIRCLEOUTLINE)
	{
		m_nParam2 = m_nParam1;
	}
	else
	{
		m_nParam2 = 2+(randomNumber() % 32);
	}

#if DEPTH == 8
	m_Color = randomNumber() % 16;
#elif DEPTH == 16
	m_Color = randomNumber();
#elif DEPTH == 32
	m_Color = COLOR32 (randomNumber() % 256, randomNumber() % 256, randomNumber() % 256, 255);
#else
	#error Screen DEPTH must be 8, 16 or 32!
#endif
	
	m_nPosX = randomNumber()%m_nDisplayWidth;
	
	m_nPosY = randomNumber()%m_nDisplayHeight;

}

CGraphicShape::~CGraphicShape (void)
{
}


/*
case GRAPHICSHAPE_RECT:
	renderer->DrawRect(m_nPosX, m_nPosY, m_nParam1, m_nParam2, m_Color);
	break;
	
case GRAPHICSHAPE_OUTLINE:
	renderer->DrawRectOutline(m_nPosX, m_nPosY, m_nParam1, m_nParam2, m_Color);
	break;
	
case GRAPHICSHAPE_LINE:
	renderer->DrawLine(m_nPosX, m_nPosY, m_nPosX+m_nParam1, m_nPosY+m_nParam2, m_Color);
	break;
	
case GRAPHICSHAPE_CIRCLE:
	renderer->DrawCircle(m_nPosX, m_nPosY, m_nParam1, m_Color);
	break;
	
case GRAPHICSHAPE_CIRCLEOUTLINE:
	renderer->DrawCircleOutline(m_nPosX, m_nPosY, m_nParam1, m_Color);
	break;
	
case GRAPHICSHAPE_SPRITE_TRANSPARENTCOLOR:
	renderer->DrawImageTransparent(m_nPosX, m_nPosY, 8, 8, spriteData, Black);
	break;

case GRAPHICSHAPE_TEXT:
	renderer->DrawText(m_nPosX, m_nPosY, m_Color, "Hello Circle!", C2DGraphics::AlignCenter);
	break;
	
	
Below this point I edited
TOC:
 -> Draw Turn
 -> Draw Selection
 -> Draw X
 -> Draw O
 -> Draw Cells
*/


/** DrawWinner , simply draws the winner on the screen
 @parm int playerNumber
*/
void CGraphicShape::DrawGameWinner(C2DGraphics* renderer, int playerNumber) {

  int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 5; // Size of each cell
  int boardX = (renderer->GetWidth() / 2) - (cellSize * 3/2);
  int boardY = (renderer->GetHeight() / 4);
  
  if(playerNumber != 0) {
  // You are the Winner Portion
  CString message;
  message.Format("Player %d you are the winner!!!", playerNumber);
  renderer->DrawText(boardX, boardY - 20, GREEN_COLOR, message);
  }
  else {
  CString message;
  message.Format("Tied game, there is no winner!!!", playerNumber);
  renderer->DrawText(boardX, boardY - 20, GREEN_COLOR, message);
  }
  
  // Play Again Portion
  boardY = (renderer->GetHeight() / 4) * 3;
  renderer->DrawText(boardX, boardY - 20, BRIGHT_WHITE_COLOR, "Would you like to play again? (y / n)");
}

/** DrawHelp

*/
void CGraphicShape::DrawHelp(C2DGraphics* renderer) {

  int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 5;
  int x = (renderer->GetWidth() / 2) + (cellSize * 3/2);
  int y = (renderer->GetHeight() / 4);
  
  // Draw X
  BoardPosition pos = {x + (cellSize * 1/4), y + (cellSize * 1/4), cellSize/2};
  renderer->DrawLine(pos.x, pos.y, pos.x + pos.size, pos.y + pos.size, RED_COLOR);
  renderer->DrawLine(pos.x + pos.size, pos.y, pos.x, pos.y + pos.size, RED_COLOR);
  
  renderer->DrawText(x + (cellSize * 1/4), y - 20, RED_COLOR, "Player 1");
  
  // Draw Circle
  y = (renderer->GetHeight() / 4) * 2;
  pos = {x, y, cellSize};
  renderer->DrawCircleOutline(pos.x + pos.size/2, pos.y + pos.size/2, pos.size/3, BLUE_COLOR);
     
  // Next to those, we will write Player 1 and Player 2
  renderer->DrawText(x + (cellSize * 1/4), y - 20, BLUE_COLOR, "Player 2");
  

}

/** Gameover, simply draws the game over screen
* @parm int p1
* @parm int p2
*/
void CGraphicShape::DrawGameOver(C2DGraphics* renderer, int p1, int p2) {

    int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 7; // Size of each cell
    int boardX = (renderer->GetWidth() / 2) - (cellSize * 2);
    int boardY = (renderer->GetHeight() / 2) - (cellSize * 3 / 2);

    int boardXX = (renderer->GetWidth() / 2) + (cellSize * 2);
    int boardYY = (renderer->GetHeight() / 2) + (cellSize * 3 / 2);

    // Draw cell border lines
    renderer->DrawLine(boardX, boardY, boardXX, boardY, BRIGHT_WHITE_COLOR);  // Top line
    renderer->DrawLine(boardXX, boardY, boardXX, boardYY, BRIGHT_WHITE_COLOR);  // Right line
    renderer->DrawLine(boardXX, boardYY, boardX, boardYY, BRIGHT_WHITE_COLOR);  // Bottom line
    renderer->DrawLine(boardX, boardYY, boardX, boardY, BRIGHT_WHITE_COLOR);  // Left line
    
    // Draw Game Over Message
    boardX = (renderer->GetWidth() / 2) - (cellSize * 0.55);
    boardY = (renderer->GetHeight() / 2) - (cellSize);
    renderer->DrawText(boardX, boardY, RED_COLOR, "GAME OVER!");
    
    // Draw Game Stats
    boardX = (renderer->GetWidth() / 2) - (cellSize);
    boardY = (renderer->GetHeight() / 2) + (cellSize * 0.75);
    
    CString message;
    message.Format("Player 1:\t %d Wins", p1);
    renderer->DrawText(boardX, boardY, RED_COLOR, message);
    
    message.Format("Player 2:\t %d Wins", p2);
    renderer->DrawText(boardX, boardY + (cellSize * 0.30), BLUE_COLOR, message);
    
}

/** Drawturn
* Draws whichever players turn it in with 1 Being X and 2 being Circle
* @parm int playerNumber
*/
void CGraphicShape::DrawTurn(C2DGraphics* renderer, int playerNumber) {

  int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 5; // Size of each cell
  int boardX = (renderer->GetWidth() / 2) - (cellSize * 3/2);
  int boardY = (renderer->GetHeight() / 2) - (cellSize * 3/2);
  
  CString message;
  message.Format("Player %d your turn!", playerNumber);

  renderer->DrawText(boardX, boardY - 20, GREEN_COLOR, message);
}

/** DrawSelection
* Draws the selector for player with 1 Being X and 2 being Circle
* @parm int row
* @parm int col
* @parm int playerNumber
*/
void CGraphicShape::DrawSelection(C2DGraphics* renderer, int row, int col) {

  int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 5; // Size of each cell
  int boardX = (renderer->GetWidth() / 2) - (cellSize * 3/2);
  int boardY = (renderer->GetHeight() / 2) - (cellSize * 3/2);
  
  int x = boardX + col * cellSize; // x coord of cell
  int y = boardY + row * cellSize; // y coord of cell
    
  renderer->DrawRect(x + cellSize*1/8, y + cellSize*1/8, cellSize*3/4, cellSize*3/4, Gray);
   
}

/** DrawX
* Draws the X rendering in a given row and column
* @parm int row
* @parm int col
*/
void CGraphicShape::DrawX(C2DGraphics* renderer, int row, int col) {
  int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 5; // Size of each cell
  int boardX = (renderer->GetWidth() / 2) - (cellSize * 3/2);
  int boardY = (renderer->GetHeight() / 2) - (cellSize * 3/2);
  
  int x = boardX + col * cellSize; // x coord of cell
  int y = boardY + row * cellSize; // y coord of cell
  
  BoardPosition pos = {x + (cellSize * 1/4), y + (cellSize * 1/4), cellSize/2};

  renderer->DrawLine(pos.x, pos.y, pos.x + pos.size, pos.y + pos.size, RED_COLOR);
  renderer->DrawLine(pos.x + pos.size, pos.y, pos.x, pos.y + pos.size, RED_COLOR);
}

/** DrawO
* Draws the Circle rendering in a given row and column
* @parm int row
* @parm int col
*/
void CGraphicShape::DrawO(C2DGraphics* renderer, int row, int col) {

  int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 5; // Size of each cell
  int boardX = (renderer->GetWidth() / 2) - (cellSize * 3/2);
  int boardY = (renderer->GetHeight() / 2) - (cellSize * 3/2);

  int x = boardX + col * cellSize; // x coord of cell
  int y = boardY + row * cellSize; // y coord of cell

  BoardPosition pos = {x, y, cellSize};

  renderer->DrawCircleOutline(pos.x + pos.size/2, pos.y + pos.size/2, pos.size/3, BLUE_COLOR);   
}

/** DrawCell
* Draws the Block/Cell rendering in a given row and column
* @parm int row
* @parm int col
*/
void CGraphicShape::DrawCell(C2DGraphics* renderer, int row, int col) {

  int cellSize = MIN(renderer->GetWidth(), renderer->GetHeight()) / 5;
  int boardX = (renderer->GetWidth() / 2) - (cellSize * 3/2);
  int boardY = (renderer->GetHeight() / 2) - (cellSize * 3/2);
 
  int x = boardX + col * cellSize; // x coord of cell
  int y = boardY + row * cellSize; // y coord of cell

  // Draw cell border lines  
  renderer->DrawLine(x, y, x + cellSize, y, BRIGHT_WHITE_COLOR);
  renderer->DrawLine(x + cellSize, y, x + cellSize, y + cellSize, BRIGHT_WHITE_COLOR);
  renderer->DrawLine(x, y + cellSize, x + cellSize, y + cellSize, BRIGHT_WHITE_COLOR);
  renderer->DrawLine(x, y, x, y + cellSize, BRIGHT_WHITE_COLOR);
}
