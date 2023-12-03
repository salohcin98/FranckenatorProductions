//
// kernel.cpp
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2021  R. Stange <rsta2@o2online.de>
// 
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
#include "kernel.h"
#include "graphicshape.h"

CKernel::CKernel (void)
: m_2DGraphics(m_Options.GetWidth (), m_Options.GetHeight ())
{
	m_ActLED.Blink (5);
}

CKernel::~CKernel (void)
{
}

boolean CKernel::Initialize (void)
{
	return m_2DGraphics.Initialize ();
}

TShutdownMode CKernel::Run (void)
{


	m_2DGraphics.ClearScreen(BLACK_COLOR);
	
	// 32 Shape Objects usable
	for (unsigned i = 0; i < nShapes; i++)
	{
		m_pShape[i] = new CGraphicShape (m_2DGraphics.GetWidth (), m_2DGraphics.GetHeight ());
	}
	
	unsigned x = 1;
	while (1)
	{
	
	// Draw Cells for Board @parm (int row, int col)
	for(int r = 0; r < 3; r++) {
	  for(int c = 0; c < 3; c++) {
	     m_pShape[x]->DrawCell(&m_2DGraphics, r, c);
	     x = x+1;
	     }
	 }
	 
	 // Draw X's and O's @parm (int row, int col)
	 m_pShape[1]->DrawX(&m_2DGraphics, 0, 1);
	 m_pShape[2]->DrawO(&m_2DGraphics, 0, 2);
	 m_pShape[1]->DrawX(&m_2DGraphics, 1, 1);
	
	 // Update Turn Text Here @parm (int playerNumber)
	 m_pShape[11]->DrawTurn(&m_2DGraphics, 1);
	 
	 m_pShape[12]->DrawSelection(&m_2DGraphics, 1, 2, 2);

	// Update...
	m_2DGraphics.UpdateDisplay();		
	}

	return ShutdownHalt;
}
