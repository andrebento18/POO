#pragma once
#include <vector>
//Existem várias “entidades” na nave.Podem ser tripulantes ou outras coisas como por exemplo invasores.
//São colectivamente referidos como “unidades”.Um tripulante será uma unidade, mas uma unidade pode não ser 
//um tripulante.Num dado instante, cada unidade estará, em princípio, numa determinada sala da nave.
#include "caracteristicas.h"
class Sala;
class Unidade{
	string nome;
	Sala *ondestou;
	int ponto_vida;
	vector <Caracteristicas*> vect_car;
public:
	Unidade(string tipo, int pv);
	virtual ~Unidade();
	virtual string toString()const;
	string getNome()const;
	int getPV()const;
	void LevaDano(int dano_recebido);
	Sala *getOndeEstou()const;
	void setOndeEstou(Sala *a);
	Caracteristicas *setCaracteristica();
	virtual void actuar();
};

class Unidade_MembroTripulacao : public Unidade {
public:
	Unidade_MembroTripulacao(string tipo);
	string toString()const;
	//void Respirar();
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