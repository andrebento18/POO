#pragma once
#include <vector>
class Caracteristica;
class Sala;
class Unidade{
	string nome;
	int ponto_vida;
	int id_unidade;
	static int conta_unidades;
	Sala *ondestou;
	vector <Caracteristica*> vect_car;
public:
	Unidade(string tipo, int pv);
	virtual ~Unidade();
	virtual string toString()const;
	string getNome()const;
	
	int getPV()const;
	void LevaDano(int dano_recebido);

	int getID_Unidade()const {
		return id_unidade;
	}
	
	Sala *getOndeEstou()const;
	void setOndeEstou(Sala *s);
	void mover_unidade(int id_unidade, Sala *sala_antiga, Sala *sala_nova);
	
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