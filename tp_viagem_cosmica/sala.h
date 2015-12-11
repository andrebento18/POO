#pragma once
#include "unidade.h"
// classe mae
class Sala {
	string tipo;
	int id_sala;
	int integridade;
	int oxigenio; //OXIGENIO
public:
	Sala(string tipo, int id_sala);
	~Sala();
	string getTipo() const;
	int getID()const;
	int getIntegridade()const;
	int getOxigenio()const;
	string toString()const;
};

// classes derivadas
class SalaPropulsor: public Sala {
	int dist_propulsao;
public:
	SalaPropulsor(string tipo, int id_sala, int propulsao);
	int getPropulsao()const;
};