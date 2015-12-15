#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "nave.h"

int random(int min, int max);

Nave::Nave() {
	cout << "Vamos preparar a nave..." << endl;
	int contador = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0 && j == 0 || i == 2 && j == 0) {
				contador++;
				salas[i][j] = new SalaPropulsor("Propulsor", 100);
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
					if (tipo_sala == "Propulsor Adicional") {
						contador++;
						salas[i][j] = new SalaPropulsoresAdicionais(tipo_sala);
						break;
					}else if (tipo_sala == "Beliche") {
						contador++;
						salas[i][j] = new SalaBeliche(tipo_sala);
						break;
					}
					else if (tipo_sala == "Raio Laser") {
						contador++;
						salas[i][j] = new SalaRaioLaser(tipo_sala);
						break;
					}else if (tipo_sala == "Auto-reparador") {
						contador++;
						salas[i][j] = new SalaAutoReparador(tipo_sala);
						break;
					}else if (tipo_sala == "Sistema de Seguranca interno") {
						contador++;
						salas[i][j] = new SalaSistemadeSegInterno(tipo_sala);
						break;
					}else if (tipo_sala == "Enfermaria") {
						contador++;
						salas[i][j] = new SalaEnfermaria(tipo_sala);
						break;
					}else if (tipo_sala == "Sala de armas") {
						contador++;
						salas[i][j] = new SalaArmas(tipo_sala);
						break;
					}else if (tipo_sala == "Alojamentos do Capitao") {
						contador++;
						salas[i][j] = new SalaAlojamentosdoCapitao(tipo_sala);
						break;
					}else if (tipo_sala == "Oficina Robotica") {
						contador++;
						salas[i][j] = new SalaOficinaRobotica(tipo_sala);
						break;
					}
					else
						cout << "Sala inexistente" << endl;
				} while (tipo_sala != "Beliche" || tipo_sala != "Propulsor Adicional" || tipo_sala != "Raio Laser" || tipo_sala == "Auto-reparador" || tipo_sala == "Sistema de Seguranca interno" || tipo_sala == "Enfermaria" || tipo_sala != "Sala de armas" || tipo_sala != "Alojamentos do Capitao" || tipo_sala != "Oficina Robotica");
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

// Devolve 0 - Nave destruida; 1 - Sa�de da Nave OK
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

int Nave::getDistancia()const {
	return distancia;
}

void Nave::setDistancia() {
	int dist_somar = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (salas[i][j] != NULL) {
				if (salas[i][j]->getTipo() == "Propulsor" || salas[i][j]->getTipo() == "Propulsor Adicional") {
					salas[i][j]->setPropulsao(); // Atualiazar potencia dos propulsores
					dist_somar += salas[i][j]->getPropulsao();
					// verificar tamb�m se a ponte est� a ser operada
				}
			}
		}
	}
	this->distancia += dist_somar;
	cout << "A nave avancou " << dist_somar << " milhas" << endl;
	cout << this->distancia << " milhas percorridas no total" << endl;
}

void Nave::evento() {
	int x = 4;// random(1, 4);
	switch (x){
	case 1:
		//Evento Chuva de meteoritos
		break;
	case 2:
		//Evento Ataque dos piratas
		break;
	case 3:
		//Evento Ataque Xenomorfo
		break;
	case 4:
		// Evento p� c�smico
		// falta implemnentar n�o calhar na mesma sala
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

//Sala * Nave::mover_para_sala(string comando_direcao, int  id){
//	for (int i = 0; i <= 2; i++){
//		for (int j = 0; j <= 4; j++){
//			if (salas[i][j]->getID() == id){
//				if (comando_direcao == "cima"){
//					if (i == 0) {
//						return salas[i][j];
//					}else{
//						int movimento = 0;
//						movimento = i;
//						movimento--;
//						return salas[movimento][j];
//					}
//				}
//				if (comando_direcao == "baixo"){
//					if (i == 2) {
//						return salas[i][j];
//						
//					}else{
//						int movimento = 0;
//						movimento = i;
//						movimento++;
//						return salas[movimento][j];
//					}
//				}
//				if (comando_direcao == "direita"){
//					if (i == 4) {
//						return salas[i][j];
//					}else{
//						int movimento = 0;
//						movimento = j;
//						movimento++;
//						return salas[i][movimento];
//					}
//				}
//				if (comando_direcao == "esquerda"){
//					if (i == 0) {
//						return salas[i][j];
//						
//					}else{
//						int movimento = 0;
//						movimento = j;
//						movimento--;
//						return salas[i][movimento];
//					}
//				}
//			}
//		}
//
//	}
//}

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

void Nave::setReparacao()
{
	/*repara dois pontos de dano a essa sala, sendo que essa repara��o
	torna - se efectiva apenas no final do turno.Os esfor�os de repara��o
	de v�rios membros da tripula��o na mesma sala s�o cumulativos(dois tripulantes � 4 pontos, etc.).
	Nota: este ponto do texto foca - se mais na sala do que no tripulante.
	Os tripulantes t�m v�rias caracter�sticas diferentes e o seu comportamento varia
	consoante essas caracter�sticas(por exemplo, se o tripulante for um robot,
	ent�o n�o repara a nave nem opera salas).*/
}