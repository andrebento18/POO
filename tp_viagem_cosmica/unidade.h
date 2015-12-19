#pragma once
#include <vector>
#include "caracteristicas.h"
class Sala;
class Unidade{
	string nome;
	int ponto_vida;
	Sala *ondestou;
	vector <Caracteristica*> vect_car;
public:
	Unidade(string tipo, int pv);
	virtual ~Unidade();
	virtual string toString()const;
	string getNome()const;
	int getPV()const;
	//void LevaDano(int dano_recebido);
	Sala *getOndeEstou()const;
	void setOndeEstou(Sala *a);
	//Caracteristica *getCaracteristica()const;
	void setCaracteristica(Caracteristica *p);
	void actua();
};

class MembroTripulacao : public Unidade {
public:
	MembroTripulacao(string tipo);
	string toString()const;
};

class Capitao : public Unidade {
public:
	Capitao(string tipo);
	/*Exoesqueleto(X): Previne os primeiros X pontos de dano em cada turno
	(excepto os danos identificados como “não pode ser evitado”).*/
	//void Exoesqueleto(int pontos_dano, int dano_ignorado);
};


class Robot : public Unidade {
	//Características: Exoesqueleto(2), Combatente(3), Tripulação
	
public:
	Robot (string tipo);
	/*Exoesqueleto(X): Previne os primeiros X pontos de dano em cada turno
	(excepto os danos identificados como “não pode ser evitado”).*/
};

//Inimigos
class Pirata : public Unidade {
	//Características: Respira, Inimigo(1, 2), Move(15)
	bool respira; //0-Nao;1-Sim
public:
	//Pirata(string tipo);
	
};