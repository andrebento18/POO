#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
#include "nave.h"

Nave::Nave() {
	cout << "Vamos preparar a nave..." << endl;
	int contador = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0 && j == 0 || i == 2 && j == 0) {
				contador += 1;
				salas[i][j] = new SalaPropulsor("Propulsor", contador, 100);
			}
			else if (i == 0 && j == 4 || i == 1 && j == 0 || i == 2 && j == 4) {
				salas[i][j] = NULL;
			}
			else if (i == 1 && j == 1) {
				contador += 1;
				salas[i][j] = new SaladeMaquinas("Sala de Maquinas", contador);
			}
			else if (i == 1 && j == 2) {
				contador += 1;
				salas[i][j] = new SalaSuportedeVida("Suporte de Vida", contador);
			}
			else if (i == 1 && j == 3) {
				contador += 1;
				salas[i][j] = new SalaControlodeEscudo("Controlo de Escudo", contador);
			}
			else if (i == 1 && j == 4) {
				contador += 1;
				salas[i][j] = new SalaPonte("Ponte", contador);
			}
			else {
				string tipo_sala;
				contador += 1;
				cout << "Tipo de sala a adicionar com id " << contador << " : ";
				getline(cin, tipo_sala);
				if (tipo_sala == "Beliche")
					salas[i][j] = new SalaBeliche(tipo_sala, contador);
				else if (tipo_sala == "Propulsor Adicional")
					salas[i][j] = new SalaPropulsoresAdicionais(tipo_sala, contador);
				else
					salas[i][j] = new Sala(tipo_sala, contador);
			}
		}
	}
	cout << "Nave criada com sucesso!" << endl;
}

Nave::~Nave() {
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 5; j++) {
				delete salas[i][j];
		}
	cout << "Nave destruida" << endl;
}

// Devolve 0 - Nave destruida; 1 - Saúde da Nave OK
int Nave::verifica_saudeNave() const
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL) {
				if (salas[i][j]->getIntegridade() == 0)
					return 0;
				else
					return 1;
			}
		}
}

int Nave::getDistancia()const {
	return distancia;
}

void Nave::setDistancia() {
	int dist_somar = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL) {
				if (salas[i][j]->getTipo() == "Propulsor" || salas[i][j]->getTipo() == "PropulsorAdicional")
					dist_somar += salas[i][j]->getPropulsao();
				// verificar também se a ponte está a ser operada
			}
		}
	}
	this->distancia += dist_somar;
	cout << "A nave avancou " << dist_somar << " milhas" << endl;
	cout << this->distancia << " milhas percorridas no total" << endl;
}

Sala * Nave::mover_para_sala(string com, int  id){
	for (int i = 0; i <= 2; i++){
		for (int j = 0; j <= 4; j++){
			if (salas[i][j]->getID() == id){
				if (com == "cima"){
					if (i == 0) {
						return salas[i][j];
					}else{
						int movimento = 0;
						movimento = i;
						movimento--;
						return salas[movimento][j];
					}
				}
				if (com == "baixo"){
					if (i == 2) {
						return salas[i][j];
						
					}else{
						int movimento = 0;
						movimento = i;
						movimento++;
						return salas[movimento][j];
					}
				}
				if (com == "direita"){
					if (i == 4) {
						return salas[i][j];
					}else{
						int movimento = 0;
						movimento = j;
						movimento++;
						return salas[i][movimento];
					}
				}
				if (com == "esquerda"){
					if (i == 0) {
						return salas[i][j];
						
					}else{
						int movimento = 0;
						movimento = j;
						movimento--;
						return salas[i][movimento];
					}
				}
			}
		}
	}
}

string Nave::getSalas()const {
	ostringstream os;
	os << "Nave com: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j <5; j++) {
			if (salas[i][j] != NULL)
				os << salas[i][j]->toString() << endl;
			else
				continue;
		}
	}
	return os.str();
}