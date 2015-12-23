#pragma once
#include "unidade.h"
#include "sala.h"
class Caracteristica {
public:
	Caracteristica() {
		cout << "Construtor basico de caracteristicas" << endl;
	};
	virtual ~Caracteristica() {
		cout << "Caracteristica eliminada" << endl;
	}
	virtual void actua_car_inicio(Unidade *u) {
	};
	virtual void actua_car_fim(Unidade *u) {
	};
};

////LISTA DE CARACTERISTICAS
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
	Respira(void) {
		respira = 2;
		cout << "Esta unidade respira" << endl;
	}
	void actua_car_inicio(Unidade *u) {
		if (u->getOndeEstou()->getOxigenio() <= 0)
			u->LevaDano(1);
		else
			u->getOndeEstou()->reduzOxigenio(respira);
	};
};

class Flamejante : public Caracteristica {
public:
	Flamejante(void) {
		cout << "Esta unidade esta envolta em chamas" << endl;
	};
	void actua_car_inicio(Unidade *u) {
		u->getOndeEstou()->reduzOxigenio(5);
	}
};

class Toxico : public Caracteristica {
public:
	Toxico(void) {
		cout << "Este ser e toxico" << endl;
	};
	void actua_car_inicio(Unidade *u) {
		/*bool unidade_toxica = false;
		Sala *p = u->getOndeEstou();
		for (unsigned int i = 0; i < p->countUnidades(); i++)
			for (unsigned int j = 0; j < p->getUnidadePosicao(i)->countCaracteristicas(); j++)
				if(p->getUnidadePosicao(i)->getCaracteristicaPosicao(j) == */
		cout << "...IMPLEMENTAR CAR.TOXICO" << endl;
	}
};

class Indeciso : public Caracteristica {
public:
	Indeciso(void) {};
	/*NAO FACO MINIMA IDEIA COMO SE PODE IMPLEMENTAR ISTO?????????????????????*/
};

class Misterioso : public Caracteristica {
	int count_turnos;
public:
	Misterioso(void) {
		count_turnos = 0;
		cout << "Sou um ser misterioso" << endl;
	};
	// NAO SEI BEM COMO SE FAZ
	/*void actua_car_fim(Unidade *u) {
		int x = random(1, 4);
		if (x == 1 && count_turnos == 0) {
			count_turnos = 1;
		}
		else if (count_turnos == 1) {
			int sala_escolhida = random(1, 12);
			u->getOndeEstou()->remover_Unidade(u);
			u->mover_unidade(u->getID_Unidade(), )
		}
	}*/
};

class Regenerador : public Caracteristica {
	int cap_regenerar;
public:
	Regenerador(int cap_regenerar) {
		this->cap_regenerar = cap_regenerar;
		cout << "Este ser e capaz de se regenerar" << endl;
	}
	void actua_car_inicio(Unidade *u) {
		if (u->getPV() + cap_regenerar < u->getPVInicial()) {
			u->setPV(cap_regenerar);
		}
	}
};

//class Exoesqueleto

class Reparador : public Caracteristica {
	int cap_reparar;
public:
	Reparador(int cap_reparar) {
		this->cap_reparar = cap_reparar;
	}
	void actua_car_fim(Unidade *u) {
		// FALTA VERIFICAR SE A UNIDADE ESTÁ EM COMBATE ??????
		if(u->getOndeEstou()->getTipo() != "Propulsor Adicional" && u->getOndeEstou()->getTipo() != "Propulsor" && u->getOndeEstou()->getIntegridade() < 100)
			u->getOndeEstou()->setIntegridade(u->getOndeEstou()->getIntegridade() + cap_reparar);
	}
};

class Operador : public Caracteristica {
public:
	Operador() {};
	void actua_car_inicio(Unidade *u) {
		//FLATA VERIFICAR TAMBÉM SE A UNIDADE NAO ESTA EM COMBATE ???????
		if (u->getOndeEstou()->getIntegridade() == 100)
			u->getOndeEstou()->setOperada(true);
	}
};

class Combatente : public Caracteristica {
	int capacidade_combate;
public:
	Combatente(int dano_que_causa) {
		this->capacidade_combate=dano_que_causa;
	}
	void actua_car_fim(Unidade *u) {
		//Tripulacao *t = new Tripulacao;
		//for (unsigned int j = 0; j < u->countCaracteristicas(); j++)
		//	if (u->getCaracteristicaPosicao(j) == t) {

		//		for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
		//			for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
		//				if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j) != t) {
		//				//Colocar Operador = FALSE
		//					//Depois de implementar o Operador
		//				}
		//			}
		//		}
		//	}
	}
};

class Tripulacao : public Caracteristica {
public:
	Tripulacao() {};
};
