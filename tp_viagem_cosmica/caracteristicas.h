#pragma once
#include "nave.h"

using namespace std;

int random(int min, int max);

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

//PENSO QUE SEJA ASSIM
class Toxico : public Caracteristica {
	int dano_toxico;
public:
	Toxico(int toxicidade):dano_toxico(toxicidade) {
		cout << "Este ser e toxico" << endl;
	};
	void actua_car_inicio(Unidade *u) {
		int existe_toxico;
		Toxico *t = new Toxico(0);
		//bool unidade_toxica = false;
		Sala *p = u->getOndeEstou();
		for (unsigned int i = 0; i < p->countUnidades(); i++) {
			existe_toxico = 0;
			for (unsigned int j = 0; j < p->getUnidadePosicao(i)->countCaracteristicas(); j++) {
				if (p->getUnidadePosicao(i)->getCaracteristicaPosicao(j) == t) {
					existe_toxico = 1;
				}
			}
			if (existe_toxico != 1) {
				p->getUnidadePosicao(i)->LevaDano(dano_toxico);
			}
		}
		
	}
};
//PENSO QUE SEJA ASSIM
class Indeciso : public Caracteristica {
	int ignora_actua_inicio;
public:
	Indeciso(void) {
		ignora_actua_inicio = 0;
	};
	//PENSO QUE SEJA ASSIM
	void actua_car_inicio(Unidade *u) {
		int x = random(1, 2);

		if (x == 1 && ignora_actua_inicio == 0) {
			ignora_actua_inicio = 1;
		}
		else if (ignora_actua_inicio == 1) {
			ignora_actua_inicio = 0;
		}
	}
	
	void actua_car_fim(Unidade *u) {
		if (ignora_actua_inicio==1)
		{
			u->setOndeEstou(u->getOndeEstava());
		}
	}
};

class Misterioso : public Caracteristica {
	int count_turnos;
public:
	Misterioso(void) {
		count_turnos = 0;
		cout << "Sou um ser misterioso" << endl;
	};
	// PENSO QUE SEJA ASSIM QUE FUNCIONE 
	// RETIREI O REMOVER UNIDADE DA SALA PORQUE A FUNÇÃO MOVER JÁ FAZ ISSO
	//CRIEI A RANDOM CAR AQUI PORQUE A FUNÇÃO RANDOM ESTAVA A DAR ERRO NÃO SEI PORQUE
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

class Exoesqueleto{
public:
	Exoesqueleto() {};
};

class Reparador : public Caracteristica {
	int cap_reparar;
public:
	Reparador(int cap_reparar) {
		this->cap_reparar = cap_reparar;
		cout << "Esta unidade repara " << cap_reparar << " pontos" << endl;
	}
	void actua_car_fim(Unidade *u) {
		// FALTA VERIFICAR SE A UNIDADE ESTÁ EM COMBATE ??????
		if(u->getOndeEstou()->getTipo() != "Propulsor Adicional" && u->getOndeEstou()->getTipo() != "Propulsor" && u->getOndeEstou()->getIntegridade() < 100)
			u->getOndeEstou()->setIntegridade(u->getOndeEstou()->getIntegridade() + cap_reparar);
	}
};

class Tripulacao : public Caracteristica {
	string tripulacao;
public:
	Tripulacao() {
		tripulacao = "TRIPULACAO";
		cout << "Faco parte da tripulacao da nave" << endl;
	};
};

class Operador : public Caracteristica {
public:
	Operador() {
		cout << "Esta unidade e capaz de operar salas" << endl;
	};
	void actua_car_inicio(Unidade *u) {
		Tripulacao *t = new Tripulacao;
		for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
			for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
				if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j) != t) {
					u->getOndeEstou()->setOperada(false);	
				}
			}
		}
		if (u->getOndeEstou()->getIntegridade() == 100)
			u->getOndeEstou()->setOperada(true);
	}
};

class Combatente : public Caracteristica {
	int capacidade_combate;
public:
	Combatente(int dano_que_causa) {
		this->capacidade_combate = dano_que_causa;
		cout << "Combatente capaz de causar " << capacidade_combate << " pontos de dano" << endl;
	}
	void actua_car_fim(Unidade *u) {
		//Tripulacao *t = new Tripulacao;
		//for (unsigned int j = 0; j < u->countCaracteristicas(); j++)
		//	if (u->getCaracteristicaPosicao(j) == t) {

		//		for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
		//			for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
		//				if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j) != t) {
		//						u->getOndeEstou()->setOperada(true);
		//					//Depois de implementar o Operador
		//				}
		//			}
		//		}
		//	}
	}
};
