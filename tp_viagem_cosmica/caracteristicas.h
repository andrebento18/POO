#pragma once
#include "nave.h"

int random(int min, int max);

class Caracteristica {
	string tipo;
public:
	Caracteristica(string tipo);
	virtual ~Caracteristica();

	string getTipoCaracterisca();

	virtual void actua_car_inicio(Unidade *u, Nave *n) {};
	virtual void actua_car_fim(Unidade *u, Nave *n) {};

	// virtual Combatente
	virtual void setCapCombate(int arma) {};

	bool operator==(Caracteristica *c) {
		if (getTipoCaracterisca() == c->getTipoCaracterisca())
			return true;
		return false;
	}
};

class Respira : public Caracteristica {
	int respira;
public:
	Respira(void);

	void actua_car_inicio(Unidade *u, Nave *n);
};

class Flamejante : public Caracteristica {
public:
	Flamejante(void);

	void actua_car_inicio(Unidade *u, Nave *n = nullptr);
};

class Toxico : public Caracteristica {
	int dano_toxico;
public:
	Toxico(int nvl_toxicd);

	void actua_car_inicio(Unidade *u, Nave *n);
};

class Indeciso : public Caracteristica {
	bool ignora_actua_inicio;
public:
	Indeciso(void);

	void actua_car_inicio(Unidade *u, Nave *n);
	void actua_car_fim(Unidade *u, Nave *n);
};

class Misterioso : public Caracteristica {
	int count_turnos;
public:
	Misterioso(void);
	
	void actua_car_fim(Unidade *u, Nave *n);
};

class Regenerador : public Caracteristica {
	int cap_regenerar;
public:
	Regenerador(int cap_regenerar);

	void actua_car_inicio(Unidade *u, Nave *n);
};

class Exoesqueleto : public Caracteristica{
	int cap_exoesqueleto;
	bool existe_inimigos;
public:
	Exoesqueleto(int cap_exoesqueleto);
	
	void actua_car_inicio(Unidade *u, Nave *n);
	void actua_car_fim(Unidade *u, Nave *n);
};

// Talvez arranjar outra maneira de implementar isto...
class Robotico : public Caracteristica {
public:
	Robotico(void);
};

class Reparador : public Caracteristica {
	int cap_reparar;
public:
	Reparador(int cap_reparar);

	void actua_car_fim(Unidade *u, Nave *n);
};

class Combatente : public Caracteristica {
	int capacidade_combate;
public:
	Combatente(int dano_que_causa);

	void setCapCombate(int arma);

	void actua_car_fim(Unidade *u, Nave *n);
};

class Xenomorfo : public Caracteristica {
	int cap_dano;
public:
	Xenomorfo(int cap_dano);
	
	void actua_car_fim(Unidade *u, Nave *n);
};

class Casulo : public Caracteristica {
	int prob_casulo;
public:
	Casulo(int prob);
	void actua_car_fim(Unidade *u, Nave *n);
};

class Mutantis_Mutandis : public Caracteristica {
	int prob;
public:
	Mutantis_Mutandis(int prob);

	// N�o sei se esta caracteristica actua no inicio ou no fim, suponho que seja no inicio ?????????????????????????
	void actua_car_inicio(Unidade *u, Nave *n);
};

class Hipnotizador : public Caracteristica {
	int prob_hip;
public:
	Hipnotizador(int prob_hip);

	// N�o sei se esta caracteristica actua no inicio ou no fim, suponho que seja no inicio ?????????????????????????
	void actua_car_inicio(Unidade *u, Nave *n);
};

class Operador : public Caracteristica {
public:
	Operador(void);
	
	void actua_car_inicio(Unidade *u, Nave *n);
};

class Tripulacao : public Caracteristica {
public:
	Tripulacao(void);
};

class Inimigo : public Caracteristica {
	int dano_unidade, dano_sala;
public:
	Inimigo(int x, int y);

	void actua_car_inicio(Unidade *u, Nave *n);
};

class Move : public Caracteristica {
	int prob_movimento;
public:
	Move(int pmovimento);

	void actua_car_inicio(Unidade *u, Nave *n);
};

class Armado : public Caracteristica {
public:
	Armado(int armado);
};