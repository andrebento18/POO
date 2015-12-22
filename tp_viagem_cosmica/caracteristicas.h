#pragma once
#include "unidade.h"
#include "sala.h"
class Caracteristica {
public:
	Caracteristica() {};
	virtual ~Caracteristica() {
		cout << "Caracteristica eliminada" << endl;
	}
	virtual void actua_car_inicio(Unidade *u) {
	};
	virtual void actua_car_fim(Unidade *u) {
	};
};

////LISTA DE CARACTERISTICAS
//bool flamejante; //0-Nao;1-Sim
//int toxico; //pontos de vida que cada unidade perde na mesma sala
//bool indeciso; //0-Nao;1-Sim 50% de prob. de ficar indeciso
//bool misterioso; //
//int exoesqueleto; //se o exoesqueleto estiver a zero o dano é recebido normal, senao recebe dano atraves da funcao exoesqueleto
//bool robotico; //caso seja robotico não pode executar accções(movimento/combate/etc) em salas com curto-circuito
//int reparador;
//int combatente; //caso hajam enimigos na mesma sala, provoca x pontos de dano a um enimigo na sala
//int xenomorfo; //
//int casulo;
//int mutatis_mutandis;//
//int hipnotizador;
//bool operador;
//bool tripulacao;
//int regenerador; //quantidade de pontos de vida que regenera por turno
//				 //bool inimigo(x,y)
//int move;
//int armado;

class Respira : public Caracteristica {
	int respira;
public:
	Respira() {
		respira = 2;
	}
	void actua_car_inicio(Unidade *u) {
		if (u->getOndeEstou()->getOxigenio() <= 0)
			u->LevaDano(1);
		else
			u->getOndeEstou()->reduzOxigenio(respira);
	};
};

class Reparador : public Caracteristica {
	int cap_reparar;
public:
	Reparador(int cap_reparar) {
		this->cap_reparar = cap_reparar;
	}
	void actua_car_fim(Unidade *u) {
		// FALTA VERIFICAR SE A UNIDADE ESTÁ EM COMBATE ??????
		if(u->getOndeEstou()->getTipo() != "Propulsor Adicional" && u->getOndeEstou()->getTipo() != "Propulsor")
			u->getOndeEstou()->setIntegridade(u->getOndeEstou()->getIntegridade() + cap_reparar);
	}
};

class Operador : public Caracteristica {
public:
	Operador() {};
	void actua_car_inicio(Unidade *u) {
		cout << "...IMPLEMENTAR CAR.OPERADOR" << endl;
	}
};

class Tripulacao : public Caracteristica {
public:
	Tripulacao() {};
};

class Combatente : public Caracteristica {
	int capacidade_combate;
public:
	Combatente(int dano_que_causa) {
		this->capacidade_combate=dano_que_causa;
	}
	void actua_car_fim(Unidade *u) {
		Tripulacao *t = new Tripulacao;
		for (unsigned int j = 0; j < u->countCaracteristicas(); j++)
			if (u->getCaracteristicaPosicao(j) == t) {

				for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
					for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
						if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j) != t) {
						//Colocar Operador = FALSE
							//Depois de implementar o Operador
						}
					}
				}
			}
	}
};