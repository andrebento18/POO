#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#include "nave.h"

Nave::Nave() {
	cout << "Nave criada" << endl;

	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 4; j++) {
			if (i == 0 && j == 0 || i == 2 && j == 0) {
				contador += 1;
				salas[i][j] = new SalaPropulsor("Propulsor", contador, salas[i][j]->getIntegridade());
			}
			else if (i == 0 && j == 4 || i == 1 && j == 0 || i == 2 && j == 4) {
				salas[i][j] = NULL;
			}
			else if (i == 1 && j == 1) {
				contador += 1;
				salas[i][j] = new Sala("Sala de Maquinas", contador);
			}
			else if (i == 1 && j == 2) {
				contador += 1;
				salas[i][j] = new Sala("Suporte de Vida", contador);
			}
			else if (i == 1 && j == 3) {
				contador += 1;
				salas[i][j] = new Sala("Controlo de Escudo", contador);
			}
			else if (i == 1 && j == 4) {
				contador += 1;
				salas[i][j] = new Sala("Ponte", contador);
			}
			else {
				string tipo_sala;
				contador += 1;
				cout << "Tipo de sala a adicionar com id " << contador << " : ";
				cin >> tipo_sala;
				salas[i][j] = new Sala(tipo_sala, contador);

			}
		}
	}
}

Nave::~Nave() {
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 5; j++) {
				delete salas[i][j];
		}
	cout << "Nave destruida" << endl;
}

int Nave::verifica_saudeNave() const
{
	//int saude = 0; isto vai ser retornado
	/*
	getIntegridade...
	getDano...
	*/
	return 100;
}

int Nave::getDistancia()const {
	return distancia;
}

void Nave::setDistancia(int dist_somar) {
	//int dist_percor; // distancia feita pelos propulsores
	//for (int i = 0; i < 3; i++)
		//for (int j = 0; j < 5; j++) {
		//	if (salas[i][j]->getTipo() == "Propulsor")
		//		salas[i][j]->getPropulsao();
		//}
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

Sala * Nave::mover_para_sala(string com, int  id) 
{
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 4; j++) 
		{
			if (salas[i][j]->getID() == id)
			{
				if (com == "cima")
				{
					if (i == 0) {
						return salas[i][j];
					}
					else
					{
						int movimento = 0;
						movimento = i;
						movimento--;
						return salas[movimento][j];
					}

				}
				if (com == "baixo")
				{
					if (i == 2) {
						return salas[i][j];
					}
					else
					{
						int movimento = 0;
						movimento = i;
						movimento++;
						return salas[movimento][j];
					}

				}
				if (com == "direita")
				{
					if (i == 4) {
						return salas[i][j];
					}
					else
					{
						int movimento = 0;
						movimento = j;
						movimento++;
						return salas[i][movimento];
					}

				}
				if (com == "esquerda")
				{
					if (i == 0) {
						return salas[i][j];
					}
					else
					{
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

