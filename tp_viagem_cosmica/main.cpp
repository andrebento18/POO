#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <MMSystem.h>
using namespace std;
#include "util.h"
#include "ConsolaG++.h"
#include "nave.h"

bool verifica_vitoria(Nave *nave, double nvl) {
	Consola c;
	if (nave->getDistancia() > 4000 + 1000  * nvl) {
		// vitória
		PlaySound(NULL, NULL, 0);
		PlaySound(TEXT("./SOUND/Victory.wav"), NULL, SND_LOOP | SND_ASYNC);
		c.clrscr();
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----VITORIA-----";
			}
			cout << endl;
		}
		cout << "Parabens, prime uma tecla para voltar ao menu inicial" << endl;
		c.getch();
		return 1;
	}else
		// sem vitória
		return 0;
}

bool verifica_derrota(Nave *nave) {
	Consola c;
	if (nave->verifica_saudeNave() == 0) {
		// derrota devido a destruicao de uma sala 
		c.clrscr();
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----GAME-OVER-----";
			}
			cout << endl;
		}
		cout << "Uma sala da tua nave foi destruida, prime uma tecla para voltar ao menu inicial e tentar novamente" << endl;
		c.getch();
		return 1;
	}
	else if (nave->countTripulacao() == 0) {
		// derrota devido a perda da tripulacao
		c.clrscr();
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----GAME-OVER-----";
			}
			cout << endl;
		}
		cout << "Ficaste sem tripulacao, prime uma tecla para voltar ao menu inicial e tentar novamente" << endl;
		c.getch();
		return 1;
	}
	else
		// sem derrota
		return 0;
}

void interface_nave(Nave *nave, int turnos) {
	Consola c;
	c.clrscr();

	cout << "Turno(s): " << turnos << "\t\t\t\tTripulacao: " << nave->countTripulacao() << " unidade(s)" << "\t\t\t\t\tInterface grafica da nave:" << endl;

	// LINHA VERTICAL
	for (int i = 0; i < 48; i++) {
		c.gotoxy(69, i);
		cout << (char)179 << endl;
		c.gotoxy(70, i);
		cout << (char)179 << endl;
	}

	// 1ª LINHA
	c.gotoxy(80, 5);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(80, 6);
	cout << (char)179 << (char)176 << "SALA:1" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 7);
	cout << (char)179 << (char)176 << "INTG: " << nave->getSala(1)->getIntegridade() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 8);
	cout << (char)179 << (char)176 << "OXIG: " << nave->getSala(1)->getOxigenio() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 9);
	cout << (char)179 << (char)176 << "OPER: " << nave->getSala(1)->getOperada() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 10);
	cout << (char)179 << (char)176 << "BREC: " << nave->getSala(1)->getBrecha() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 11);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(100, 5);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(100, 6);
	cout << (char)179 << (char)176 << "SALA:2" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 7);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 8);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 9);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 10);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 11);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(120, 5);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(120, 6);
	cout << (char)179 << (char)176 << "SALA:3" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 7);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 8);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 9);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 10);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 11);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(140, 5);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(140, 6);
	cout << (char)179 << (char)176 << "SALA:4" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 7);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 8);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 9);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 10);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 11);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	// 2ª LINHA

	c.gotoxy(100, 12);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(100, 13);
	cout << (char)179 << (char)176 << "SALA:5" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 14);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 15);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 16);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 17);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 18);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(120, 12);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(120, 13);
	cout << (char)179 << (char)176 << "SALA:6" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 14);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 15);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 16);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 17);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 18);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(140, 12);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(140, 13);
	cout << (char)179 << (char)176 << "SALA:7" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 14);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 15);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 16);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 17);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 18);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(160, 12);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(160, 13);
	cout << (char)179 << (char)176 << "SALA:8" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(160, 14);
	cout << (char)179 << (char)176 << "INTG: " << nave->getSala(8)->getIntegridade() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(160, 15);
	cout << (char)179 << (char)176 << "OXIG: " << nave->getSala(8)->getOxigenio() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(160, 16);
	cout << (char)179 << (char)176 << "OPER: " << nave->getSala(8)->getOperada() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(160, 17);
	cout << (char)179 << (char)176 << "BREC: " << nave->getSala(8)->getBrecha() << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(160, 18);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	// 3ª LINHA
	c.gotoxy(80, 19);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(80, 20);
	cout << (char)179 << (char)176 << "SALA:9" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 21);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 22);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 23);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 24);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(80, 25);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(100, 19);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(100, 20);
	cout << (char)179 << (char)176 << "SALA:10" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 21);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 22);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 23);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 24);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(100, 25);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(120, 19);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(120, 20);
	cout << (char)179 << (char)176 << "SALA:11" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 21);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 22);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 23);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 24);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(120, 25);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	c.gotoxy(140, 19);
	cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
	c.gotoxy(140, 20);
	cout << (char)179 << (char)176 << "SALA:12" << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 21);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 22);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 23);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 24);
	cout << (char)179 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)176 << (char)179 << '\n';
	c.gotoxy(140, 25);
	cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';

	for (int i = 3; i == 33; i += 10) {
		for (int j = 1; j <= 12; j++) {
			c.gotoxy(80, i);
			cout << "INTG: " << nave->getSala(j)->getIntegridade() << endl;
		}
	}

	c.gotoxy(1, 1);
	cout << nave->getSalas() << "Distancia total percorrida: " << nave->getDistancia() << endl;
}

void viagem(Nave *nave, double nvl) {
	Consola c;
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("./SOUND/Space_Cruise.wav"), NULL, SND_LOOP | SND_ASYNC);
	c.clrscr();
	/////////////// VIAGEM ///////////////
	int turnos = 0;
	int event_ocurr = 0;
	do {
		c.clrscr();
		// 1. INICIO DO TURNO
		turnos++;
		
		nave->inicio_turno();

		// 2. FASE DE ORDENS
		string cmd;
		do {
			interface_nave(nave, turnos);
			
			cout << "De as ordens meu comandante...\nCMD> "; cin >> cmd;
			if (cmd == "mover") {
				int id_unidade;
				string dir_mov;
				cout << "Que unidade deseja mover? "; cin >> id_unidade;
				cout << "Para que sala? (Segundo uma orientação) "; cin >> dir_mov; cout << endl;

				nave->check_mov_sala(id_unidade, dir_mov);
			}
			else if (cmd == "fim")
			{
				return;
			}
			else if(cmd != "avancar" && cmd != "fim") {
				cout << "Nao conheco esse comando meu comandante..." << endl;
				c.getch();
			}
		} while (cmd != "avancar");

		// 3. FINAL DO TURNO

		nave->fim_turno();

		// 4. EVENTOS
		if (event_ocurr == 0) {
			nave->evento();
			event_ocurr = random(5, 10);
		}
		else {
			event_ocurr--;
			cout << "Estamos com sorte, nao tivemos precalcos a avancar comandante!" << endl;
		}

		cout << "Prime uma tecla pra avancar o turno..." << endl;
		c.getch();
	} while (verifica_vitoria(nave, nvl) == 0 && verifica_derrota(nave) == 0);
}

void ajuda() {
	Consola c;
	c.clrscr();
	c.gotoxy(20, 20);
	cout << "... IMPLEMENTAR MENU-AJUDA" << endl;
	c.getch();
}

void menu_inicial() {
	Consola c;
	c.clrscr();
	c.setTextColor(c.VERDE_CLARO);
	c.setBackgroundColor(c.PRETO);

	string cmd;
	do {
		PlaySound(NULL, NULL, 0);
		PlaySound(TEXT("./SOUND/Cosmos.wav"), NULL, SND_LOOP | SND_ASYNC);
		c.clrscr();
		c.gotoxy(21, 18);
		cout << "VIAGEM-COSMICA" << endl;
		c.gotoxy(15, 21);
		cout << "Escreva o que deseja fazer: \n\t\t\t<jogar> \n\t\t\t<ajuda> \n\t\t\t<fim>\n" << endl;
		c.gotoxy(15, 25);
		cout << "CMD> "; cin >> cmd;
		if (cmd == "jogar") {
			double nvl;
			do {
				c.clrscr();
				c.gotoxy(20, 20);
				cout << "Insira a dificuldade da missao: ";
				cin >> nvl;
			} while (nvl <= 0);

			c.clrscr();

			Nave nave;

			c.gotoxy(20, 20);
			cout << "Prima uma tecla para comecar a viagem..." << endl;
			c.getch();

			viagem(&nave, nvl);
		}
		else if (cmd == "ajuda") {
			ajuda();
		}
	} while (cmd != "fim");
}

int main(void) {
	system("mode 650");

	menu_inicial();

	return 0;
}


