#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "nave.h"

bool verifica_vitoria(Nave *nave, int nvl) {
	if (nave->getDistancia() > 400 * /*1000 * */ nvl) {
		// vitória
		system("CLS");
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
		system("CLS");
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

void avanca_nave(Nave *nave) {
	nave->setDistancia();
}

void viagem(Nave *nave, int nvl) {
	system("CLS");
	/////////////// VIAGEM ///////////////
	int turnos = 0;
	do {
		// 1. INICIO DO TURNO
		turnos++;
		cout << "Turno(s): " << turnos << endl;
		
		cout << nave->getSalas();

		system("pause");

		// 2. FASE DE ORDENS

		// 3. FINAL DO TURNO

		// 4. EVENTOS

		avanca_nave(nave);
	} while (verifica_vitoria(nave, nvl) == 0 && verifica_derrota(nave) == 0);	//... || tripulantes == 0)
}

//Como não consegui arranjar a cena da sala propulsor tentei fazer o movimento da unidade pelas salas da nave
//penso que esteja bem, mas dá uma olhadela e vê se concordas, se não concordares, diz-me o que errei para ter
//uma noção.
void mover_unidade(string comando, Unidade *u1, Nave *nave, int id_sala_actual) {
	u1->setOndeEstou(NULL);
	Sala *a;
	a = nave->mover_para_sala(comando, id_sala_actual);
	u1->setOndeEstou(a);
}

int main(void) {
	string cmd;
	do {
		system("CLS");
		cout << "VIAGEM-COSMICA" << endl;
		cout << "Insira jogar ou fim" << endl;
		cout << "CMD> "; cin >> cmd;
		if(cmd == "jogar"){
			int nvl;
			cout << "Insira a dificuldade da missao: ";
			cin >> nvl;
			
			system("CLS");

			/////////////// PREPARACAO DA NAVE ///////////////
			Nave nave;

			cout << "Prima uma tecla para comecar a viagem..." << endl;
			system("pause");

			viagem(&nave, nvl);
		}
	} while (cmd != "fim");

	return 0;
}