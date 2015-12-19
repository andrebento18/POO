#pragma once
#include <vector>
#include "unidade.h"
class Sala {
	string tipo;
	int id_sala;
	static int conta;
	int integridade;
	bool operada;
	int oxigenio;
	int propulsao;
	vector <Unidade*> unidades;
public:
	Sala(string tipo);
	virtual ~Sala();
	virtual string toString()const;
	string getTipo() const;
	int getID()const;
	int getIntegridade()const;
	void setIntegridade(int valor_integridade);
	bool getOperada()const;
	void setOperada(bool valor);
	int getOxigenio()const;
	void reduzOxigenio(int oxig_reduzir);
	
	void adicionar_Unidade(Unidade *unidade_a_adicionar);
	// Propulsor virutal functions
	virtual int getPropulsao()const { return propulsao; };
	void setPropulsao(int propulsao) {
		this->propulsao = propulsao;
	};
	// Ponte virtual functions
	virtual void setOperada() {};

	int getUnidades()const;
	Unidade* getUnidade(int id)const;
};

class SalaPropulsor : public Sala {
public:
	SalaPropulsor(string tipo, int propulsao);
	void propulsiona()const;
	virtual string toString()const;
};

class SaladeMaquinas : public Sala {
public:
	SaladeMaquinas(string tipo);
	virtual string toString()const;
};

class SalaSuportedeVida : public Sala {
public:
	SalaSuportedeVida(string tipo);
	virtual string toString()const;
};

class SalaControlodeEscudo : public Sala {
public:
	SalaControlodeEscudo(string tipo);
	virtual string toString()const;
};

class SalaPonte : public Sala {
public:
	SalaPonte(string tipo);
	virtual void setOperada();
	virtual string toString()const;
};

class SalaBeliche : public Sala {
public:
	SalaBeliche(string tipo);
	virtual string toString()const;
};

class SalaRaioLaser : public Sala {
public:
	SalaRaioLaser(string tipo);
	virtual string toString()const;
};

class SalaAutoReparador : public Sala {
public:
	SalaAutoReparador(string tipo);
	virtual string toString()const;
};

class SalaSistemadeSegInterno : public Sala {
public:
	SalaSistemadeSegInterno(string tipo);
	virtual string toString()const;
};

class SalaEnfermaria : public Sala {
public:
	SalaEnfermaria(string tipo);
	virtual string toString()const;
};

class SalaArmas : public Sala {
public:
	SalaArmas(string tipo);
	virtual string toString()const;
};

class SalaAlojamentosdoCapitao : public Sala {
public:
	SalaAlojamentosdoCapitao(string tipo);
	virtual string toString()const;
};

class SalaOficinaRobotica : public Sala {
public:
	SalaOficinaRobotica(string tipo);
	virtual string toString()const;
};
