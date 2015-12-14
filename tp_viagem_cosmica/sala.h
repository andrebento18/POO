#pragma once
#include <vector> // ???
#include "unidade.h"
// classe mae
class Sala {
	string tipo;
	int id_sala;
	int integridade;
	int oxigenio;
	vector <Unidade*> unidades;
public:
	Sala(string tipo, int id_sala);
	~Sala();
	string getTipo() const;
	int getID()const;
	int getIntegridade()const;
	void setIntegridade(int valor_integridade);
	int getOxigenio()const;
	string toString()const;
	// Propulsor virutal functions
	virtual int getPropulsao()const { return getPropulsao(); }; // ????? � preciso andar com funcoes virtuais para obter as das derivadas???
	virtual void setPropulsao() {};
	// Ponte virtual functions
	virtual void setOperada()const {};
};

// classes derivadas de Sala
class SalaPropulsor : public Sala {
	int dist_propulsao;
public:
	SalaPropulsor(string tipo, int id_sala, int propulsao);
	int getPropulsao() const;
	void setPropulsao();
};

class SaladeMaquinas : public Sala {
public:
	SaladeMaquinas(string tipo, int id_sala);
};

class SalaSuportedeVida : public Sala {
public:
	SalaSuportedeVida(string tipo, int id_sala);
};

class SalaControlodeEscudo : public Sala {
public:
	SalaControlodeEscudo(string tipo, int id_sala);
};

class SalaPonte : public Sala {
	bool operada;
public:
	SalaPonte(string tipo, int id_sala);
	void setOperada()const;
};

class SalaPropulsoresAdicionais : public Sala {
	int cap_propulsao;
public:
	SalaPropulsoresAdicionais(string tipo, int id_sala);
	int getPropulsao() const; 
	void setPropulsao();
};

class SalaBeliche : public Sala {
public:
	SalaBeliche(string tipo, int id_sala);
};

//PropulsoresAdicionais;Beliches;RaioLaser;Auto-Reparador;
//SistemadeSegInterno;Enfermaria;SalaArmas;AlojamentodoCap;OficinaRobotica