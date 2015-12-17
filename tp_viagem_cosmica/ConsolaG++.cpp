
/* Funcoes da consola. Dez 2010 */

/* Pequenas correcoes. Nov. 2013 */

#include "ConsolaG++.h"                      
#include <windows.h>
#include <stdio.h>

Consola::Consola() {
	hconsola = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle (STD_INPUT_HANDLE);	
}

void Consola::gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hconsola,coord);
}
   
void Consola::clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	const COORD startCoords = {0,0};   
	DWORD dummy;
  
	GetConsoleScreenBufferInfo(hconsola,&csbi);
	FillConsoleOutputCharacter(hconsola,
                               ' ',
                               csbi.dwSize.X * csbi.dwSize.Y,
                               startCoords,
                               &dummy);    
	FillConsoleOutputAttribute(hconsola,
							   csbi.wAttributes,
                               csbi.dwSize.X * csbi.dwSize.Y,
                               startCoords,
							   & dummy);
	gotoxy(0,0);
}

void Consola::setTextColor(WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsola,&csbi);
	WORD cor = csbi.wAttributes;
	cor &= 0xFFF0;
	cor |= color;
	// duvidas acerca destas duas linhas -> TI ou TAC
	SetConsoleTextAttribute(hconsola,cor);
	return;
}

void Consola::setBackgroundColor(WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsola,&csbi);
	WORD cor = csbi.wAttributes;
	cor &= 0xFF0F;
	cor |= (color << 4);
	// duvidas acerca destas duas linhas -> TI ou TAC
	SetConsoleTextAttribute(hconsola,cor);
}

void Consola::setScreenSize(int nLinhas, int nCols) {
	COORD tam;
	SMALL_RECT DisplayArea;

	tam.X = nCols;
	tam.Y = nLinhas;
	SetConsoleScreenBufferSize(hconsola, tam);   // isto muda o tamanho da matriz de caracteres

	DisplayArea.Top = 0;
	DisplayArea.Left = 0;
	DisplayArea.Bottom = nLinhas-1;
	DisplayArea.Right = nCols-1;
    SetConsoleWindowInfo(hconsola, TRUE, &DisplayArea);  // isto muda o tamanho da area da janela em caracteres
}


char Consola::getch(void) {
	INPUT_RECORD irInputRecord;
	DWORD dwEventsRead;
	CHAR cChar;

	while(ReadConsoleInputA(hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
		if (irInputRecord.EventType == KEY_EVENT
			&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
			&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
			&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
		{

		cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
		ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */

		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) return ESQUERDA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) return DIREITA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP) return CIMA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) return BAIXO;

		return cChar;
    }
  return EOF;
}


// setTextSize - Usar isto apenas se a outra nï¿½o funcionar (XP ou menos)
// O mï¿½todo de funcionamento ï¿½ bastante forï¿½a-bruta
//   Procura uma fonte que cumpra os requisitos do novo tamanho
//   e muda para essa fonte (ou seja, muda tambï¿½ma fonte)
// Funï¿½ï¿½es que a MS nem se deu ao trabalho de documentar
// Help: http://blogs.microsoft.co.il/blogs/pavely/archive/2009/07/23/changing-console-fonts.aspx
typedef BOOL (WINAPI * SetConsoleFont_)(HANDLE ConsoleOutput, DWORD FontIndex); // kernel32!SetConsoleFont
typedef BOOL (WINAPI * GetConsoleFontInfo_)(HANDLE ConsoleOutput, BOOL Unknown1, DWORD Unknown2, PCONSOLE_FONT_INFO ConsoleFontInfo); // kernel32!GetConsoleFontInfo
typedef DWORD (WINAPI * GetNumberOfConsoleFonts_)(); // kernel32!GetNumberOfConsoleFonts

