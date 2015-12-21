#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "nave.h"

#define PROPULSORADICIONAL "Propulsor Adicional"
#define BELICHE "Beliche"
#define RAIOLASER "Raio Laser"
#define AUTOREPARADOR "Auto-reparador"
#define SISTEMASEGINTERNO "Sistema de Seguranca interno"
#define ENFERMARIA "Enfermaria"
#define SALAARMAS "Sala de armas"
#define ALOJCAPITAO "Alojamentos do Capitao"
#define OFICROBOTICA "Oficina Robotica"

int random(int min, int max);

Nave::Nave() {
	cout << "Vamos preparar a nave para a viagem..." << endl;
	int contador = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0 && j == 0 || i == 2 && j == 0) {
				contador++;
				salas[i][j] = new SalaPropulsor("Propulsor");
			}
			else if (i == 0 && j == 4 || i == 1 && j == 0 || i == 2 && j == 4) {
				salas[i][j] = NULL;
			}
			else if (i == 1 && j == 1) {
				contador++;
				salas[i][j] = new SaladeMaquinas("Sala de Maquinas");
			}
			else if (i == 1 && j == 2) {
				contador++;
				salas[i][j] = new SalaSuportedeVida("Suporte de Vida");
			}
			else if (i == 1 && j == 3) {
				contador++;
				salas[i][j] = new SalaControlodeEscudo("Controlo de Escudo");
			}
			else if (i == 1 && j == 4) {
				contador++;
				salas[i][j] = new SalaPonte("Ponte");
			}
			else {
				string tipo_sala;
				do {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Tipo de sala a adicionar com id " << contador << " : ";
					getline(cin, tipo_sala);
					if (tipo_sala == PROPULSORADICIONAL) {
						contador++;
						salas[i][j] = new SalaPropulsor(tipo_sala);
						break;
					}
					else if (tipo_sala == BELICHE) {
						contador++;
						salas[i][j] = new SalaBeliche(tipo_sala);
						break;
					}
					else if (tipo_sala == RAIOLASER) {
						contador++;
						salas[i][j] = new SalaRaioLaser(tipo_sala);
						break;
					}
					else if (tipo_sala == AUTOREPARADOR) {
						contador++;
						salas[i][j] = new SalaAutoReparador(tipo_sala);
						break;
					}
					else if (tipo_sala == SISTEMASEGINTERNO) {
						contador++;
						salas[i][j] = new SalaSistemadeSegInterno(tipo_sala);
						break;
					}
					else if (tipo_sala == ENFERMARIA) {
						contador++;
						salas[i][j] = new SalaEnfermaria(tipo_sala);
						break;
					}
					else if (tipo_sala == SALAARMAS) {
						contador++;
						salas[i][j] = new SalaArmas(tipo_sala);
						break;
					}
					else if (tipo_sala == ALOJCAPITAO) {
						contador++;
						salas[i][j] = new SalaAlojamentosdoCapitao(tipo_sala);
						break;
					}
					else if (tipo_sala == OFICROBOTICA) {
						contador++;
						salas[i][j] = new SalaOficinaRobotica(tipo_sala);
						break;
					}
					else
						cout << "A sala que pretende criar nao e possivel!" << endl;
				} while (tipo_sala != BELICHE || tipo_sala != PROPULSORADICIONAL || tipo_sala != RAIOLASER || tipo_sala == AUTOREPARADOR || tipo_sala == SISTEMASEGINTERNO || tipo_sala == ENFERMARIA || tipo_sala != SALAARMAS || tipo_sala != ALOJCAPITAO || tipo_sala != OFICROBOTICA);
			}
		}
	}
	cout << "Nave criada com sucesso comandante!" << endl;
	cout << "Prime uma tecla para avancar...";
	system("pause");
	system("CLS");
	cout << "Agora vamos adicionar os tripulantes a tua nave!\n";

	int conta_mebros_trip = 3;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 5; j++) {
			if(salas[i][j] != NULL)
				if (salas[i][j]->getTipo() == BELICHE) {
					conta_mebros_trip++;
				}
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL) {
				if (salas[i][j]->getTipo() == ALOJCAPITAO) {
					Unidade *p = new Capitao("Capitao");
					//AGREGA A UNIDADE AO VECTOR DE UNIDADES DA SALA
					salas[i][j]->adicionar_Unidade(p);
					//SETA A SALA ONDE ESTA A UNIDADE
					p->setOndeEstou(salas[i][j]);
					cout << "Capitao adicionado a Sala Alojamento do Capitao!\n";
					conta_mebros_trip--;
				}
				else if (salas[i][j]->getTipo() == OFICROBOTICA) {
					Unidade *p = new Robot("Robot");
					//AGREGA A UNIDADE AO VECTOR DE UNIDADES DA SALA
					salas[i][j]->adicionar_Unidade(p);
					//SETA A SALA ONDE ESTA A UNIDADE
					p->setOndeEstou(salas[i][j]);
					cout << "Robot adicionado a Sala Oficina Robotica!\n";
					conta_mebros_trip--;
				}
			}
		}
	}

	do{
		Unidade *p = new MembroTripulacao("Membro de Tripulacao");
		//AGREGA A UNIDADE AO VECTOR DE UNIDADES DA SALA
		salas[1][4]->adicionar_Unidade(p);
		//SETA A SALA ONDE ESTA A UNIDADE
		p->setOndeEstou(salas[1][4]);
		cout << "Membro da tripulaçao adicionado a Sala Ponte!\n";
		conta_mebros_trip--;
	} while (conta_mebros_trip != 0);
	cout << "Tripulantes adicionados a nave com sucesso comandante!" << endl;
	cout << "Prime uma tecla para avancar...";
	system("pause");
	system("cls");
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
	int verifica_saude = 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL)
				if (salas[i][j]->getIntegridade() == 0)
					verifica_saude = 0;
		}
	return verifica_saude;
}

Sala *Nave::getSala(int id_sala)const {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++) 
			if (salas[i][j] != NULL && salas[i][j]->getID() == id_sala){
				return salas[i][j];
				break;
			}
}

string Nave::getSalas()const {
	ostringstream os;
	os << "Nave com: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL) 
				os << salas[i][j]->toString();
			else
				continue;
		}
	}
	return os.str();
}

int Nave::getDistancia()const {
	return distancia;
}

void Nave::inicio_turno() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			if (salas[i][j] != NULL) 
				salas[i][j]->unidades_actuar();
}

void Nave::check_mov_sala(int id_unidade, string comando_direcao){
	// Obter id_sala onde se encontra a unidade
	int id_sala;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			if (salas[i][j] != NULL)
				if (salas[i][j]->getUnidade(id_unidade) != NULL) {
					id_sala = salas[i][j]->getID();
				}
	cout << "id_unidade " << id_unidade << "id_sala " << id_sala << endl;
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 4; j++)
			if(salas[i][j] != NULL)
				if (salas[i][j]->getID() == id_sala) {
					if (comando_direcao == "cima") {
						if (i == 0 || i == 1 && j == 4 || i == 2 && j == 0) {
							cout << "Nao podemos mover a unidade " << id_unidade << "para a sala a norte comandante!" << endl;
							break;
						}
						else
							salas[i][j]->getUnidade(id_unidade)->mover_unidade(id_unidade, salas[i][j], salas[i + 1][j]);
					}
					else if (comando_direcao == "baixo") {
						if (i == 2 || i == 0 && j == 0 || i == 1 && j == 4) {
							cout << "Nao podemos mover a unidade " << id_unidade << "para a sala a sul comandante!" << endl;
							break;
						}
						else 
							salas[i][j]->getUnidade(id_unidade)->mover_unidade(id_unidade, salas[i][j], salas[i - 1][j]);
					}
					else if (comando_direcao == "direita") {
						if (j == 4 || j == 3 && i == 0 || j == 3 && i == 2) {
							cout << "Nao podemos mover a unidade " << id_unidade << "para a sala a este comandante!" << endl;
							break;
						}
						else 
							salas[i][j]->getUnidade(id_unidade)->mover_unidade(id_unidade, salas[i][j], salas[i][j + 1]);
					}
					else if (comando_direcao == "esquerda") {
						if (j == 0 && j == 1 && i == 1) {
							cout << "Nao podemos mover a unidade " << id_unidade << "para a sala a este comandante!" << endl;
							break;
						}
						else 
							salas[i][j]->getUnidade(id_unidade)->mover_unidade(id_unidade, salas[i][j], salas[i][j - 1]);
					}
					else
						cout << "Comandante, essa unidade ou esse movimento nao e possivel" << endl;
				}
}

void Nave::avancaNave() {
	int dist_somar = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL) {
				if ((salas[i][j]->getTipo() == "Propulsor" || salas[i][j]->getTipo() == PROPULSORADICIONAL) && salas[1][1]->getIntegridade() == 100 && salas[1][4]->getOperada() == true) {
					dist_somar += salas[i][j]->getIntegridade();
				}
			}
		}
	}
	this->distancia += dist_somar;
	cout << "A nave avancou " << dist_somar << " milhas" << endl;
	cout << this->distancia << " milhas percorridas no total" << endl;
}

void Nave::evento() {
	int x = random(1, 4);
	switch (x){
	case 1:
		//Evento Chuva de meteoritos
		cout << "... IMPLEMENTAR CHUVA DE METEORITOS" << endl;
		break;
	case 2:
		//Evento Ataque dos piratas
		cout << "... IMPLEMENTAR ATAQUE DOS PIRATAS" << endl;
		break;
	case 3:
		//Evento Ataque Xenomorfo
		cout << "... IMPLEMENTAR ATAQUE XENOMORFO" << endl;
		break;
	case 4:
		// Evento pó cósmico
		// falta implemnentar não calhar na mesma sala
		int n_salas_afetadas = random(3, 5);
		while (n_salas_afetadas != 0) {
			int i = random(0, 2);
			int j = random(0, 4);
			if (salas[i][j] != NULL) {
				n_salas_afetadas--;
				salas[i][j]->setIntegridade(salas[i][j]->getIntegridade() - 10);
				cout << "A sala " << salas[i][j]->getTipo() << ", " << salas[i][j]->getID() << " recebeu um dano de 10" << endl;
			}
		}
		break;
	}
}