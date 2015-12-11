#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "nave.h"

bool verifica_vitoria(Nave *nave, int *nvl) {
	if (nave->getDistancia() > 400 * 1000 * *nvl) {
		// vitória
		system("CLS");//llll
		cout << "VITORIA" << endl;
		return 1;
	}
	else
		// sem vitória
		return 0;
}

bool verifica_derrota(Nave *nave) {
	if (nave->verifica_saudeNave() == 0)
		// derrota
		return 1;
	else
		// sem derrota
		return 0;
}

Nave *prep_nave() {
	system("CLS");
	/////////////// PREPARACAO DA NAVE ///////////////
	cout << "Vamos preparar a nave..." << endl;
	//PropulsoresAdicionais;Beliches;RaioLaser;Auto-Reparador;
	//SistemadeSegInterno;Enfermaria;SalaArmas;AlojamentodoCap;OficinaRobotica

	Nave nave;
	
	cout << nave.getSalas();
	
	return &nave;
}

void viagem(Nave *nave, int *nvl) {
	system("CLS");
	/////////////// VIAGEM ///////////////
	int turnos = 0;
	do {
		turnos++;
		cout << "Turno(s): " << turnos << endl;

		// 1. INICIO DO TURNO

		// 2. FASE DE ORDENS

		// 3. FINAL DO TURNO

		// 4. EVENTOS

	} while (verifica_vitoria(nave, nvl) == 0 && verifica_derrota(nave) == 0);	//... || tripulantes == 0)
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

			Nave *nave = prep_nave();

			system("pause");

			viagem(nave, &nvl);
		}
	} while (cmd != "fim");

	return 0;
}