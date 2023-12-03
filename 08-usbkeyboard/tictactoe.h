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

  private:
       
        boolean checkPlace(void);
        boolean checkWin(void);
        static void Player1Wins(void);
        static void Player2Wins(void);
        

  private:
        volatile GameStatus m_status;
        int       cur_row;
        int       cur_col;
        int       turn;
        int       grid[3][3];
        int       player1wins;
        int       player2wins;
        int       moves;
        
        static TicTacToe *game;
            
};



#endif
