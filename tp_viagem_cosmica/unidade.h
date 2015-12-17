#pragma once
#include <vector>
//Existem v�rias �entidades� na nave.Podem ser tripulantes ou outras coisas como por exemplo invasores.
//S�o colectivamente referidos como �unidades�.Um tripulante ser� uma unidade, mas uma unidade pode n�o ser 
//um tripulante.Num dado instante, cada unidade estar�, em princ�pio, numa determinada sala da nave.
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
	(excepto os danos identificados como �n�o pode ser evitado�).*/
	//void Exoesqueleto(int pontos_dano, int dano_ignorado);
};


class Robot : public Unidade {
	//Caracter�sticas: Exoesqueleto(2), Combatente(3), Tripula��o
	
public:
	Robot (string tipo);
	/*Exoesqueleto(X): Previne os primeiros X pontos de dano em cada turno
	(excepto os danos identificados como �n�o pode ser evitado�).*/
};

//Inimigos
class Pirata : public Unidade {
	//Caracter�sticas: Respira, Inimigo(1, 2), Move(15)
	bool respira; //0-Nao;1-Sim
public:
	//Pirata(string tipo);
	
};