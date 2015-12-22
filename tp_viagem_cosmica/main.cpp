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
		PlaySound(NULL, NULL, 0);
		PlaySound(TEXT("./SOUND/Victory.wav"), NULL, SND_LOOP | SND_ASYNC);
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
		// derrota devido a destruicao de uma sala 
		system("cls");
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----GAME-OVER-----";
			}
			cout << endl;
		}
		cout << "Uma sala da tua nave foi destruida, prime uma tecla para voltar ao menu inicial e tentar novamente" << endl;
		system("pause");
		return 1;
	}
	else if (nave->countTripulacao() == 0) {
		// derrota devido a perda da tripulacao
		system("cls");
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----GAME-OVER-----";
			}
			cout << endl;
		}
		cout << "Ficaste sem tripulacao, prime uma tecla para voltar ao menu inicial e tentar novamente" << endl;
		system("pause");
		return 1;
	}
	else
		// sem derrota
		return 0;
}

void interface_nave(Nave *nave, int turnos) {
	system("cls");
	cout << "Turno(s): " << turnos << "\tTripulacao: " << nave->countTripulacao() << " unidade(s)" << endl << nave->getSalas() << endl << "Distancia total percorrida: " << nave->getDistancia() << endl;
}

void viagem(Nave *nave, double nvl) {
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("./SOUND/Space_Cruise.wav"), NULL, SND_LOOP | SND_ASYNC);
	system("cls");
	/////////////// VIAGEM ///////////////
	int turnos = 0;
	int event_ocurr = 0;
	do {
		system("cls");
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
			/*else if(cmd != "avancar")
				cout << "Nao conheco esse comando meu comandante..." << endl;
			system("pause");*/
			else if (cmd == "fim")
			{
				exit(0);
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
			cout << "Esta com sorte, nao tivemos precalcos a avancar comandante!" << endl;
		}

		cout << "Prime uma tecla pra avancar o turno..." << endl;
		system("pause");
		
	} while (verifica_vitoria(nave, nvl) == 0 && verifica_derrota(nave) == 0);
}

void ajuda() {
	system("cls");
	cout << "...IMPLEMENTAR MENU DE AJUDA" << endl;
	system("pause");
}

void menu_inicial() {
	Consola c;
	c.clrscr();
	c.setScreenSize(45, 80);
	c.setTextColor(c.VERDE_CLARO);
	c.setBackgroundColor(c.PRETO);

	string cmd;
	do {
		PlaySound(NULL, NULL, 0);
		//PlaySound(TEXT("./SOUND/Cosmos.wav"), NULL, SND_LOOP | SND_ASYNC);
		c.clrscr();
		cout << "VIAGEM-COSMICA" << endl;
		cout << "Escreva o que deseja fazer: \n\t<jogar> \n\t<ajuda> \n\t<fim>\n" << endl;
		cout << "CMD> "; cin >> cmd;
		if (cmd == "jogar") {
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
		else if (cmd == "ajuda") {
			ajuda();
		}
	} while (cmd != "fim");
}

int main(void) {

	menu_inicial();

	return 0;
}


