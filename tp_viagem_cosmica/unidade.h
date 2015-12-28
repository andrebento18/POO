#pragma once
#include <vector>

using namespace std;

class Caracteristica;
class Sala;
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
	virtual string toString()const;
	string getNome()const;
	
	int getPV()const;
	int getPVInicial()const;
	void setPV(int new_ponto_vida);
	void LevaDano(int dano_recebido);

	int getID_Unidade()const {
		return id_unidade;
	}
	
	Sala *getOndeEstou()const;
	Sala * getOndeEstava() const;
	void setOndeEstou(Sala *s);
	void setOndeEstava(Sala * s);
	void mover_unidade(int id_unidade, Sala *sala_antiga, Sala *sala_nova);
	
	void setCaracteristica(Caracteristica *p);
	Caracteristica *getCaracteristica(Caracteristica *p);
	Caracteristica *getCaracteristicaPosicao(int posicao);
	unsigned int countCaracteristicas()const;

	void actua_inicio();
	void actua_fim();
};

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
public:
	CasulodeGeigermorfo(string tipo);
};

class Blob :public Unidade {
public:
	Blob(string tipo);
};

class Mxyzypykwi :public Unidade {
public:
	Mxyzypykwi(string tipo);
};