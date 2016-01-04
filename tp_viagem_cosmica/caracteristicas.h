#pragma once
#include "nave.h"

using namespace std;

int random(int min, int max);

class Caracteristica {
	string tipo;
public:
	Caracteristica(string tipo) {
		this->tipo = tipo;
	};
	virtual ~Caracteristica() {
		cout << "Caracteristica eliminada" << endl;
	}
	string getTipoCaracterisca() {
		return tipo;
	}

	virtual void actua_car_inicio(Unidade *u, Nave *n) {
	};
	virtual void actua_car_fim(Unidade *u, Nave *n) {
	};

	virtual int getArmacao(void) {
		return 0;
	};
};

class Respira : public Caracteristica {
	int respira;
public:
	Respira(void):Caracteristica("Respira") {
		respira = 2;
		cout << "Esta unidade respira" << endl;
	}
	void actua_car_inicio(Unidade *u, Nave *n) {
		if (u->getOndeEstou()->getOxigenio() <= 0)
			u->LevaDano(1);
		else 
			u->getOndeEstou()->reduzOxigenio(respira);
	};
};

class Flamejante : public Caracteristica {
public:
	Flamejante(void):Caracteristica("Flamejante") {
		cout << "Esta unidade esta envolta em chamas" << endl;
	};
	void actua_car_inicio(Unidade *u, Nave *n) {
		u->getOndeEstou()->reduzOxigenio(5);
	}
};

class Toxico : public Caracteristica {
	int dano_toxico;
public:
	Toxico(int toxicidade):Caracteristica("Toxico"), dano_toxico(toxicidade) {
		cout << "Este ser e toxico" << endl;
	};
	void actua_car_inicio(Unidade *u, Nave *n) {
		bool existe_toxico;
		bool unidade_toxica = false;
		Sala *p = u->getOndeEstou();
		for (unsigned int i = 0; i < p->countUnidades(); i++) {
			existe_toxico = false;
			for (unsigned int j = 0; j < p->getUnidadePosicao(i)->countCaracteristicas(); j++) {
				if (p->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca() == "Toxico") {
					existe_toxico = true;
					break;
				}
			}
			if (existe_toxico != true) {
				p->getUnidadePosicao(i)->LevaDano(dano_toxico);
			}
		}
		
	}
};

class Indeciso : public Caracteristica {
	bool ignora_actua_inicio;
public:
	Indeciso(void):Caracteristica("Indeciso") {
		ignora_actua_inicio = false;
	};
	void actua_car_inicio(Unidade *u, Nave *n) {
		int x = random(1, 2);

		if (x == 1 && ignora_actua_inicio == false) {
			ignora_actua_inicio = true;
		}
		else if (ignora_actua_inicio == true) {
			ignora_actua_inicio = false;
		}
	}
	
	void actua_car_fim(Unidade *u, Nave *n) {
		if (ignora_actua_inicio == true){
			u->setOndeEstou(u->getOndeEstava());
		}
	}
};

class Misterioso : public Caracteristica {
	int count_turnos;
public:
	Misterioso(void):Caracteristica("Misterioso") {
		count_turnos = 0;
		cout << "Sou um ser misterioso" << endl;
	};
	
	void actua_car_fim(Unidade *u, Nave *n) {
		int x = random(1, 4);
		if (x == 1 && count_turnos == 0) {
			count_turnos = 1;
		}
		else if (count_turnos == 1) {
			int sala_escolhida = random(1, 12);
			u->getOndeEstou()->remover_Unidade(u);
			u->mover_unidade(u->getID_Unidade(), u->getOndeEstou(), n->getSala(sala_escolhida));
			int indeciso = random(1, 2);
		}
	}
};

class Regenerador : public Caracteristica {
	int cap_regenerar;
public:
	Regenerador(int cap_regenerar):Caracteristica("Regenerador") {
		this->cap_regenerar = cap_regenerar;
		cout << "Este ser e capaz de regenerar " << cap_regenerar << " pontos de vida por turno" << endl;
	}
	void actua_car_inicio(Unidade *u, Nave *n) {
		if (u->getPV() + cap_regenerar < u->getPVInicial()) {
			u->aumentaPV(cap_regenerar);
		}
	}
};

class Exoesqueleto : public Caracteristica{
	//int cap_exoesqueleto;
public:
	Exoesqueleto(/*x pontos de dano*/):Caracteristica("Exoesqueleto") {
	};
};

// Talvez arranjar outra maneira de implementar isto...
//class Robotico : public Caracteristica;

class Reparador : public Caracteristica {
	int cap_reparar;
public:
	Reparador(int cap_reparar):Caracteristica("Reparador") {
		this->cap_reparar = cap_reparar;
		cout << "Esta unidade repara " << cap_reparar << " pontos, por turno, da sala onde esta" << endl;
	}
	void actua_car_fim(Unidade *u, Nave *n) {
		bool existe_inimigos = false;
		if (u->getOndeEstou()->getTipo() != "Propulsor Adicional" && u->getOndeEstou()->getTipo() != "Propulsor" && u->getOndeEstou()->getIntegridade() < 100){
			for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
				for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
					if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca() != "Tripulacao") {
						existe_inimigos = true;
						cout << "Passei";
					}
				}
			}
			if (existe_inimigos == false)
				u->getOndeEstou()->aumentaIntergridade(cap_reparar);
			if (u->getNome() == "Blob")
				u->getOndeEstou()->aumentaIntergridade(cap_reparar);
		}
	}
};

class Combatente : public Caracteristica {
	int capacidade_combate;
public:
	Combatente(int dano_que_causa):Caracteristica("Combatente") {
		this->capacidade_combate = dano_que_causa;
		cout << "Combatente capaz de causar " << capacidade_combate << " pontos de dano" << endl;
	}
	void actua_car_fim(Unidade *u, Nave *n) {
		int	escolhe_alvo = 0, elemento_trip = 0;
		int ja_ataquei = 0;
			
		for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
			for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
				if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca() != "Tripulacao") {
					u->getOndeEstou()->setOperada(false);
					break;
				}
				else {
					u->getOndeEstou()->setOperada(true);
				}
			}
		}
		
		if (u->getOndeEstou()->getOperada() == false) {
			do {
				escolhe_alvo = random(0, u->getOndeEstou()->countUnidades());
				/*for (unsigned int j = 0; j < u->getOndeEstou()->getUnidadePosicao(escolhe_alvo)->countCaracteristicas(); j++) {
					if (u->getOndeEstou()->getUnidadePosicao(escolhe_alvo)->getCaracteristicaPosicao(j)->getTipoCaracterisca() == "Tripulacao") {
						elemento_trip = 1;
						break;
					}
				}*/
				if (elemento_trip != 1) {
					int dano_armado = 0;
					for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
						if (u->getCaracteristicaPosicao(j)->getTipoCaracterisca() == "Armado") {
							dano_armado = u->getCaracteristicaPosicao(j)->getArmacao();
						}	
					}
					//u->getOndeEstou()->getUnidadePosicao(escolhe_alvo)->LevaDano(dano_armado + capacidade_combate);
					break;
				}
			} while (ja_ataquei != 1);
		}
	}
};
//??????????????????????????????????????????????????????????????????????????????????????????
class Xenomorfo : public Caracteristica {
	int cap_dano;
public:
	Xenomorfo(int cap_dano) :Caracteristica("Xenomorfo") {
		this->cap_dano = cap_dano;
	}
	//void actua_car_fim(Unidade *u, Nave *n) {
	//	bool existe_inimigo = false;
	//	for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
	//		//for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
	//		//	if(u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca != "Xenomorfo")
	//		//		// Verificar se é enimigo, caso sim atacar um aleatório
	//		//		// Aproveitar combatente
	//		//}
	//	}
	//}
};

class Mutantis_Mutandis : public Caracteristica {
	int prob;
public:
	Mutantis_Mutandis(int prob):Caracteristica("Mutantis_Mutandis") {
		this->prob = prob;
		cout << "Esta unidade é capaz de alterar a sala onde se encontra com " << prob << " % probabilidade" << endl;
	}
	// Não sei se esta caracteristica actua no inicio ou no fim
	//void actua_car_inicio(Unidade *u, Nave *n) {
	//	//if()
	//	//	// Copiar a sala para outro tipo de sala aleatório
	//}
};
//??????????????????????????????????????????????????????????????????????????????????????????????????????

class Operador : public Caracteristica {
public:
	Operador(void):Caracteristica("Operador") {
		cout << "Esta unidade e capaz de operar salas" << endl;
	}
	void actua_car_inicio(Unidade *u, Nave *n) {
		for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
			for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
				if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca() != "Tripulacao") {
					u->getOndeEstou()->setOperada(false);
				}
			}
		}
		if (u->getOndeEstou()->getIntegridade() == 100)
			u->getOndeEstou()->setOperada(true);
	}
};

class Tripulacao : public Caracteristica {
public:
	Tripulacao(void):Caracteristica("Tripulacao") {
		cout << "Faco parte da tripulacao da nave" << endl;
	}
};

class Move : public Caracteristica {
	int prob_movimento;
public:
	Move(int pmovimento) :Caracteristica("Move"), prob_movimento(pmovimento) {
		cout << "Sou capaz de me mover!" << endl;
	}
	void actua_car_inicio(Unidade *u, Nave *n) {
		if (random(1, 100) < prob_movimento){
			// Obter id_sala onde se encontra a unidade
			int id_sala = u->getOndeEstou()->getID();
			// Sortear o movimento "cima", "baixo", "esquerda", "direita"
			string comando_direcao;
			bool moveu = false;
			do {
				switch (random(1, 4)) {
				case 1: comando_direcao = "cima";
					break;
				case 2: comando_direcao = "baixo";
					break;
				case 3: comando_direcao = "esquerda";
					break;
				case 4: comando_direcao = "direita";
					break;
				}
				// Verificar a possibilidade de movimento e efectuá-lo caso seja possível
				for (int i = 0; i <= 2; i++)
					for (int j = 0; j <= 4; j++)
						if (n->getSalaMatriz(i, j) != NULL)
							if (n->getSalaMatriz(i, j)->getID() == id_sala) {
								if (comando_direcao == "cima") {
									if (i == 0 || i == 1 && j == 4 || i == 2 && j == 0 || n->getSalaMatriz(i + 1, j) == NULL) {
										break;
									}
									else {
										u->mover_unidade(u->getID_Unidade(), n->getSalaMatriz(i, j), n->getSalaMatriz(i + 1, j));
										moveu = true;
										cout << "movi" << endl;
										system("pause");
									}
								}
								else if (comando_direcao == "baixo") {
									if (i == 2 || i == 0 && j == 0 || i == 1 && j == 4 || n->getSalaMatriz(i - 1, j) == NULL) {
										break;
									}
									else {
										u->mover_unidade(u->getID_Unidade(), n->getSalaMatriz(i, j), n->getSalaMatriz(i - 1, j));
										moveu = true;
										cout << "movi" << endl;
										system("pause");
									}
								}
								else if (comando_direcao == "direita") {
									if (j == 4 || j == 3 && i == 0 || j == 3 && i == 2 || n->getSalaMatriz(i, j + 1) == NULL) {
										break;
									}
									else {
										u->mover_unidade(u->getID_Unidade(), n->getSalaMatriz(i, j), n->getSalaMatriz(i, j + 1));
										moveu = true;
										cout << "movi" << endl;
										system("pause");
									}
								}
								else if (comando_direcao == "esquerda") {
									if (j == 0 && j == 1 && i == 1 || n->getSalaMatriz(i, j - 1) == NULL) {
										break;
									}
									else {
										u->mover_unidade(u->getID_Unidade(), n->getSalaMatriz(i, j), n->getSalaMatriz(i, j - 1));
										moveu = true;
										cout << "movi" << endl;
										system("pause");
									}
								}
								else
									break;
							}
			} while (moveu == false);
		}
	}
};

class Armado : public Caracteristica {
	int capacidade_armacao;
public:
	Armado(int armado) :Caracteristica("Armado"), capacidade_armacao(armado) {
		cout << "Estou Armado" << endl;
	}
	int getArmacao(void) {
		return capacidade_armacao;
	};
};