#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <MMSystem.h>
using namespace std;
#include "ConsolaG++.h"
#include "util.h"
#include "nave.h"

bool verifica_vitoria(Nave *nave, double nvl) {
	if (nave->getDistancia() > 4000 + 1000  * nvl) {
		// vitória
		system("cls");
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----VITORIA-----";
			}
			cout << endl;
		}
		cout << "Parabens, prime uma tecla para voltar ao menu inicial" << endl;
		system("pause");
		return 1;
	}else
		// sem vitória
		return 0;
}

bool verifica_derrota(Nave *nave) {
	if (nave->verifica_saudeNave() == 0) {
		// derrota
		system("cls");
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----GAME-OVER-----";
			}
			cout << endl;
		}
		cout << "Perdeste o jogo, prime uma tecla para voltar ao menu inicial e tentar novamente" << endl;
		system("pause");
		return 1;
	}else
		// sem derrota
		return 0;
}

void viagem(Nave *nave, double nvl) {
	system("cls");
	/////////////// VIAGEM ///////////////
	int turnos = 0;
	int event_ocurr = 0;
	do {
		system("cls");
		// 1. INICIO DO TURNO
		turnos++;
		
		nave->inicio_turno();
		
		cout << "Turno(s): " << turnos << endl;
		// Apenas para efeitos de display
		cout << nave->getSalas();

		// 2. FASE DE ORDENS

		// 3. FINAL DO TURNO

		// 4. EVENTOS
		if (event_ocurr == 0) {
			nave->evento();
			event_ocurr = random(5, 10);
		}else
			event_ocurr--;

		nave->avancaNave();
		cout << "Prime uma tecla pra avancar o turno..." << endl;
		system("pause");
	} while (verifica_vitoria(nave, nvl) == 0 && verifica_derrota(nave) == 0);	//... || tripulantes == 0)
}

//Como não consegui arranjar a cena da sala propulsor tentei fazer o movimento da unidade pelas salas da nave
//penso que esteja bem, mas dá uma olhadela e vê se concordas, se não concordares, diz-me o que errei para ter
//uma noção.
//void mover_unidade(string comando, Unidade *u1, Nave *nave, int id_sala_actual) {
//	u1->setOndeEstou(NULL);
//	Sala *a;
//	a = nave->mover_para_sala(comando, id_sala_actual);
//	u1->setOndeEstou(a);
//}

int main(void) {
	PlaySound(TEXT("./SOUND/Space_Cruise.wav"), NULL, SND_ASYNC);
	
	Consola c;
	c.clrscr();
	c.setScreenSize(45, 80);
	c.setTextColor(c.VERDE_CLARO);
	c.setBackgroundColor(c.PRETO);

	string cmd;
	do {
		c.clrscr();
		cout << "VIAGEM-COSMICA" << endl;
		cout << "Insira jogar ou fim" << endl;
		cout << "CMD> "; cin >> cmd;
		if(cmd == "jogar"){
			double nvl;
			do {
				cout << "Insira a dificuldade da missao: ";
				cin >> nvl;
			} while (nvl <= 0);
			
			system("cls");

			Nave nave;

			cout << "Prima uma tecla para comecar a viagem..." << endl;
			system("pause");

			viagem(&nave, nvl);
		}
	} while (cmd != "fim");

	return 0;
}


