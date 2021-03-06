#pragma once
#include <vector>

using namespace std;

class Caracteristica;
class Sala;
class Nave;
class Unidade{
	string nome;
	int ponto_vida;
	static int ponto_vida_inicial;
	int id_unidade;
	static int conta_unidades;
	Sala *ondestou;
	Sala *ondestava;
	vector <Caracteristica*> vect_car;
public:
	Unidade(string tipo, int pv);
	virtual ~Unidade();
	string toString();
	string getNome()const;
	
	int getPV()const;
	int getPVInicial()const;
	void setPV(int new_ponto_vida);
	void aumentaPV(int valor_aumentar);
	virtual void LevaDano(int dano_recebido);

	int getID_Unidade()const;
	
	Sala *getOndeEstou();
	Sala * getOndeEstava();
	void setOndeEstou(Sala *s);
	void setOndeEstava(Sala * s);
	void mover_unidade(Sala *sala_antiga, Sala *sala_nova);
	void mata_unidade();
	
	void setCaracteristica(Caracteristica *p);
	Caracteristica *getCaracteristica(Caracteristica *p);
	Caracteristica *getCaracteristicaPosicao(int posicao);
	Caracteristica *getCaracteristicaTipo(string tipo);
	unsigned int countCaracteristicas()const;

	virtual void actua_inicio(Nave *n);
	virtual void actua_fim(Nave *n);
};

// Unidades
class MembroTripulacao : public Unidade {
public:
	MembroTripulacao(string tipo);
};

class Capitao : public Unidade {
public:
	Capitao(string tipo);
};


class Robot : public Unidade {
public:
	Robot (string tipo);
};

//Inimigos
class Pirata : public Unidade {
public:
	Pirata(string tipo);
};

//Xenomorfos
class Geigermorfo :public Unidade {
public:
	Geigermorfo(string tipo);
};

class CasulodeGeigermorfo :public Unidade {
	Unidade *unidade_aprisionada;
	int turno;
public:
	CasulodeGeigermorfo(string tipo, Unidade *u);

	void actua_incio(Nave *n);
	void actua_fim(Nave *n);
};

class Blob :public Unidade {
public:
	Blob(string tipo);
};

class Mxyzypykwi :public Unidade {
public:
	Mxyzypykwi(string tipo);
};