#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define PROPULSORADICIONAL "Propulsor Adicional"
#define BELICHE "Beliche"
#define RAIOLASER "Raio Laser"
#define AUTOREPARADOR "Auto-reparador"
#define SISTEMASEGINTERNO "Sistema de Seguranca interno"
#define ENFERMARIA "Enfermaria"
#define SALAARMAS "Sala de armas"
#define ALOJCAPITAO "Alojamentos do Capitao"
#define OFICROBOTICA "Oficina Robotica"

#include "ConsolaG++.h"
#include "nave.h"

int random(int min, int max);

Nave::Nave() {
	//Consola c;
	Consola c("comandos.txt");
	cout << "Vamos preparar a nave para a viagem..." << endl;
	int contador = 1;
	bool ck_aloj_cap = false;
	bool ck_ofic_rob = false;
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
					//cin.clear();
					//cin.ignore(1, '\r\n');
					c.setTextColor(c.CINZENTO);
					cout << "Salas possiveis de adicionar: " << endl << "\t->Propulsor Adicional" << "\t->Beliche" << "\t->Raio Laser" << "\t->Auto-reparador" << endl << "\t->Sistema de Seguranca interno" << "\t->Enfermaria" << "\t->Sala de armas" << "\t->Alojamentos do Capitao" << endl << "\t->Oficina Robotica" << endl;
					c.setTextColor(c.VERDE_CLARO);
					cout << "Tipo de sala a adicionar com id " << contador << " : ";
					getline(*c.entrada, tipo_sala);

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
					else if (tipo_sala == ALOJCAPITAO && ck_aloj_cap == false) {
						contador++;
						salas[i][j] = new SalaAlojamentosdoCapitao(tipo_sala);
						ck_aloj_cap = true;
						break;
					}
					else if (tipo_sala == OFICROBOTICA && ck_ofic_rob == false) {
						contador++;
						salas[i][j] = new SalaOficinaRobotica(tipo_sala);
						ck_ofic_rob = true;
						break;
					}
					else
						cout << "A sala que pretende adicionar nao e possivel!" << endl;
				} while (tipo_sala != BELICHE || tipo_sala != PROPULSORADICIONAL || tipo_sala != RAIOLASER || tipo_sala == AUTOREPARADOR || tipo_sala == SISTEMASEGINTERNO || tipo_sala == ENFERMARIA || tipo_sala != SALAARMAS || tipo_sala != ALOJCAPITAO || tipo_sala != OFICROBOTICA);
			}
		}
	}
	cout << "Nave criada com sucesso comandante!" << endl;
	cout << "Prime uma tecla para avancar...";
	c.getch();
	c.clrscr();

	cout << "Agora vamos adicionar os tripulantes a tua nave!" << endl;

	int conta_mebros_trip = 3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++) 
			if(salas[i][j] != NULL)
				if (salas[i][j]->getTipo() == BELICHE) 
					conta_mebros_trip++;

	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 5; j++) 
			if (salas[i][j] != NULL) {
				if (salas[i][j]->getTipo() == ALOJCAPITAO) {
					Unidade *p = new Capitao("Capitao");
					//AGREGA A UNIDADE AO VECTOR DE UNIDADES DA SALA
					salas[i][j]->adicionar_Unidade(p);
					cout << "Capitao adicionado a Sala Alojamento do Capitao!\n";
					conta_mebros_trip--;
				}
				else if (salas[i][j]->getTipo() == OFICROBOTICA) {
					Unidade *p = new Robot("Robot");
					//AGREGA A UNIDADE AO VECTOR DE UNIDADES DA SALA
					salas[i][j]->adicionar_Unidade(p);
					cout << "Robot adicionado a Sala Oficina Robotica!\n";
					conta_mebros_trip--;
				}
			}

	do{
		Unidade *p = new MembroTripulacao("Membro de Tripulacao");
		//AGREGA A UNIDADE AO VECTOR DE UNIDADES DA SALA
		salas[1][4]->adicionar_Unidade(p);
		//SETA A SALA ONDE ESTA A UNIDADE
		cout << "Membro da tripulacao adicionado a Sala Ponte!\n";
		conta_mebros_trip--;
	} while (conta_mebros_trip != 0);
	cout << endl << "Tripulantes adicionados a nave com sucesso comandante!" << endl;
	cout << "Prime uma tecla para avancar...";
	c.getch();
	c.clrscr();
}

Nave::~Nave() {
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 5; j++) 
				delete salas[i][j];

	cout << "Nave destruida" << endl;
}

// Devolve 0 - Nave destruida; 1 - Saúde da Nave OK
int Nave::verifica_saudeNave() const {
	int verifica_saude = 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			if (salas[i][j] != NULL)
				if (salas[i][j]->getIntegridade() == 0)
					verifica_saude = 0;

	return verifica_saude;
}

int Nave::countTripulacao()const {
	int quant_trip = 0;
	for (int i = 1; i <= 12; i++) {
		quant_trip += getSala(i)->countUnidades();
	}
	return quant_trip;
}

Sala *Nave::getSala(int id_sala)const {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++) 
			if (salas[i][j] != NULL && salas[i][j]->getID() == id_sala){
				return salas[i][j];
				break;
			}
}

Sala * Nave::getSalaMatriz(int i, int j) const {
	return salas[i][j];
}

string Nave::getSalas()const {
	ostringstream os;
	os << "Nave com: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL)
				os << salas[i][j]->toString() << endl;
			else
				continue;
		}
	}
	return os.str();
}

int Nave::getDistancia()const {
	return distancia;
}

void Nave::setDistancia(int dist_somar) {
	distancia += dist_somar;
}

void Nave::inicio_turno() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			if (salas[i][j] != NULL) {
				salas[i][j]->unidades_actuar_inicio(this);
				salas[i][j]->salas_actuar_inicio(this);
			}
}

void Nave::fim_turno() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			if (salas[i][j] != NULL) {
				salas[i][j]->unidades_actuar_fim(this);
				salas[i][j]->salas_actuar_fim(this);
			}
}

bool Nave::check_mov_sala(int id_unidade, string comando_direcao) {
	// Obter id_sala onde se encontra a unidade
	int id_sala = 0;
	int tipo_unidade = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			if (salas[i][j] != NULL) {
				if (salas[i][j]->countUnidades() != 0) {
					if (salas[i][j]->getUnidade(id_unidade) != NULL) {
						tipo_unidade = 1;
						id_sala = salas[i][j]->getID();
					}
				}
				else if (salas[i][j]->countPiratas() != 0) {
					if (salas[i][j]->getPirata(id_unidade) != NULL) {
						tipo_unidade = 2;
						id_sala = salas[i][j]->getID();
					}
				}
				else if (salas[i][j]->countXenomorfo() != 0) {
					if (salas[i][j]->getXenomorfo(id_unidade) != NULL) {
						tipo_unidade = 3;
						id_sala = salas[i][j]->getID();
					}
				}
			}

	// Verificar a possibilidade de movimento e efectuá-lo caso seja possível
	for (int i = 0; i <= 2; i++)
		for (int j = 0; j <= 4; j++)
			if (salas[i][j] != NULL)
				if (salas[i][j]->getID() == id_sala) {
					if (comando_direcao == "cima") {
						if (i == 0 || i == 1 && j == 4 || i == 2 && j == 0) {
							return false;
						}
						else {
							if (tipo_unidade == 1) {
								salas[i][j]->getUnidade(id_unidade)->mover_unidade(salas[i][j], salas[i - 1][j]);
								return true;
							}
							else if (tipo_unidade == 2) {
								salas[i][j]->getPirata(id_unidade)->mover_unidade(salas[i][j], salas[i - 1][j]);
								return true;
							}
							else if (tipo_unidade == 3) {
								salas[i][j]->getXenomorfo(id_unidade)->mover_unidade(salas[i][j], salas[i - 1][j]);
								return true;
							}
						}
					}
					else if (comando_direcao == "baixo") {
						if (i == 2 || i == 0 && j == 0 || i == 1 && j == 4) {
							return false;
						}
						else {
							if (tipo_unidade == 1) {
								salas[i][j]->getUnidade(id_unidade)->mover_unidade(salas[i][j], salas[i + 1][j]);
								return true;
							}
							else if (tipo_unidade == 2) {
								salas[i][j]->getPirata(id_unidade)->mover_unidade(salas[i][j], salas[i + 1][j]);
								return true;
							}
							else if (tipo_unidade == 3) {
								salas[i][j]->getXenomorfo(id_unidade)->mover_unidade(salas[i][j], salas[i + 1][j]);
								return true;
							}
						}
					}
					else if (comando_direcao == "direita") {
						if (j == 4 || j == 3 && i == 0 || j == 3 && i == 2) {
							return false;
						}
						else {
							if (tipo_unidade == 1) {
								salas[i][j]->getUnidade(id_unidade)->mover_unidade(salas[i][j], salas[i][j + 1]);
								return true;
							}
							else if (tipo_unidade == 2) {
								salas[i][j]->getPirata(id_unidade)->mover_unidade(salas[i][j], salas[i][j + 1]);
								return true;
							}
							else if (tipo_unidade == 3) {
								salas[i][j]->getXenomorfo(id_unidade)->mover_unidade(salas[i][j], salas[i][j + 1]);
								return true;
							}
						}
					}
					else if (comando_direcao == "esquerda") {
						if (j == 0 || j == 1 && i == 1) {
							return false;
						}
						else {
							if (tipo_unidade == 1) {
								salas[i][j]->getUnidade(id_unidade)->mover_unidade(salas[i][j], salas[i][j - 1]);
								return true;
							}
							else if (tipo_unidade == 2) {
								salas[i][j]->getPirata(id_unidade)->mover_unidade(salas[i][j], salas[i][j - 1]);
								return true;
							}
							else if (tipo_unidade == 3) {
								salas[i][j]->getXenomorfo(id_unidade)->mover_unidade(salas[i][j], salas[i][j - 1]);
								return true;
							}
						}
					}
				}
}

void dano_meteoritos(Nave *n, int n_meteoritos) {
	for (int i = n_meteoritos; i > 0; i--) {
		if (n->getSala(7)->getEscudo() == 0) {
			int sala_random = random(1, 12);
			n->getSala(sala_random)->reduzIntegridade(10);
			cout << "A integridade da Sala: " << n->getSala(sala_random)->getID() << "   " << n->getSala(sala_random)->getTipo() << " foi reduzida em 10 pontos" << endl;
			n->getSala(sala_random)->setBrecha(true);
			cout << "Oh nao!!! Foi provocada uma brecha na sala " << n->getSala(sala_random)->getID() << "   " << n->getSala(sala_random)->getTipo() << endl;
		}
		else {
			n->getSala(7)->reduzEscudo(10);
			cout << "O Escudo danificado em 10 pontos" << endl;
		}
	}
}

void dano_piratas(Nave *n, int dano_ataque_piratas) {
	if (dano_ataque_piratas > n->getSala(7)->getEscudo()) {
		int excesso = dano_ataque_piratas - n->getSala(7)->getEscudo();
		int sala_random = random(1, 12);
		n->getSala(sala_random)->reduzIntegridade(excesso);
		int problema = random(1, 3);
		switch (problema) {
			case 1: n->getSala(sala_random)->setFogo(true);
			case 2: n->getSala(sala_random)->setBrecha(true);
			case 3: n->getSala(sala_random)->setCurtoCircuito(true);
		}
	}
	else
		n->getSala(7)->reduzEscudo(dano_ataque_piratas);
	cout << "Os piratas atacaram a nossa nave comandante, foram provocados " << dano_ataque_piratas << " pontos de dano" << endl;
}

void Nave::evento() {
	int x = random(3, 3);
	switch (x) {
		case 1: {
			//Evento Chuva de meteoritos
			cout << "\tCHUVA DE METEORITOS" << endl << endl;
			//Check quantos raio laser operados existem na nave
			int raio_laser_oper = 0;
			for (int i = 1; i <= 12; i++)
				if (getSala(i)->getTipo() == RAIOLASER && getSala(i)->getOperada() == true)
					raio_laser_oper += 1;

			if (getSala(8)->getOperada() == false) {
				int n_meteoritos = random(6, 12);
				if (raio_laser_oper > 0) {
					for (int i = raio_laser_oper; i > 0; i--) {
						int n_ciclos = n_meteoritos;
						//Contra-ataque do raio laser
						for (int i = n_ciclos; i > 0; i--) {
							int prob = random(0, 1);
							if (prob == 1)
								n_meteoritos -= 1;
						}
					}
				}
				dano_meteoritos(this, n_meteoritos);
			}
			else {
				int n_meteoritos = random(4, 8);
				if (raio_laser_oper > 0) {
					for (int i = raio_laser_oper; i > 0; i--) {
						int n_ciclos = n_meteoritos;
						//Contra-ataque do raio laser
						for (int i = n_ciclos; i > 0; i--) {
							int prob = random(0, 1);
							if (prob == 1)
								n_meteoritos -= 1;
						}
					}
				}
				dano_meteoritos(this, n_meteoritos);
			}
			break;
		}

		case 2: {
			cout << "\tATAQUE DOS PIRATAS" << endl << endl;
			// Dano provocado pelo disparo dos piratas
			int dano_disparo_piratas = random(30, 60);

			dano_piratas(this, dano_disparo_piratas);

			// Check quantos raio laser operados existem na nave
			int raio_laser_oper = 0;
			for (int i = 1; i <= 12; i++)
				if (getSala(i)->getTipo() == RAIOLASER && getSala(i)->getOperada() == true)
					raio_laser_oper += 1;

			// Retaliação da Nave ou invasão dos Piratas
			if (raio_laser_oper > 0)
				break;
			else {
				int n_piratas = random(3, 5);
				int sala_random = random(1, 12);
				for (int i = n_piratas; i > 0; i--) {
					Unidade *p = new Pirata("Pirata");
					getSala(sala_random)->adicionar_Unidade(p);
				}
				cout << n_piratas << " piratas invadiram a nossa nave comandante, temos que ter cuidado" << endl;
			}
			break;
		}

		case 3: {
			cout << "\tATAQUE XENOMORFO" << endl;
			int alien_random = random(1, 3);
			int sala_random = random(1, 12);
			if (alien_random == 1) {
				Unidade *p = new Geigermorfo("Geigermorfo");
				getSala(sala_random)->adicionar_Unidade(p);
			}
			else if (alien_random == 2) {
				Unidade *p = new Blob("Blob");
				getSala(sala_random)->adicionar_Unidade(p);
			}
			else if (alien_random == 3) {
				Unidade *p = new Mxyzypykwi("Mxyzypykwi");
				getSala(sala_random)->adicionar_Unidade(p);
			}
			cout << endl << "Fomos invadidos por um ser alienigena comandante" << endl;
			break;
		}
		
		case 4: {
			// FALTA IMPLEMENTAR NAO CALHAR NAO CALHAR NA MESMA SALA ??????????????????
			cout << "\tPO COSMICO" << endl;
			int n_salas_afetadas = random(3, 5);
			while (n_salas_afetadas != 0) {
				int sala_random = random(1, 12);
				n_salas_afetadas--;
				getSala(sala_random)->reduzIntegridade(10);
				cout << "Devido ao po cosmico que atravessamos, a sala: " << getSala(sala_random)->getID() << ", " << getSala(sala_random)->getTipo() << " recebeu um dano de 10 pontos comandante." << endl;
			}
			break;
		}
	}
}