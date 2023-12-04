// This file belongs strictly to FranckenatorProductions
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2023  Chase Poland, Nicholas Franck, Eric Peasley.

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
#ifndef _tictactoe_h
#define _tictactoe_h


#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/devicenameservice.h>
#include <circle/screen.h>
#include <circle/serial.h>
#include <circle/exceptionhandler.h>
#include <circle/interrupt.h>
#include <circle/timer.h>
#include <circle/logger.h>
#include <circle/usb/usbhcidevice.h>
#include <circle/usb/usbkeyboard.h>
#include <circle/types.h>
#include "graphicshape.h"
#include <circle/2dgraphics.h>

enum GameStatus
{
	Initial,
	Ongoing,
	Winner,
	Gameover
};

class TicTacToe
{


  public:
        TicTacToe (void);
	~TicTacToe (void);
	void Initialize();
        void moveUp(void);
        void moveDown(void);
        void moveRight(void);
        void moveLeft(void);
        void placeTic(void);
        GameStatus getStatus(void);
        void GameOver(void);
        

  private:
       
        boolean checkPlace(void);
        boolean checkWin(void);
        static void Player1Wins(void);
        static void Player2Wins(void);
        void RedrawGameState(void);
        

  private:
        static const unsigned nShapes = 32;
        volatile GameStatus m_status;
        int       cur_row;
        int       cur_col;
        int       turn;
        int       grid[3][3];
        int       player1wins;
        int       player2wins;
        int       moves;
        CKernelOptions		m_Options;
        CGraphicShape		*m_pShape[nShapes];
        C2DGraphics		m_2DGraphics;
	
        static TicTacToe *game;
            
};



#endif
