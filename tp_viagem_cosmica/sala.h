#pragma once
#include <vector>
#include "unidade.h"
class Nave;
class Sala {
	string tipo;
	int id_sala;
	static int conta_salas;
	int integridade;
	/*int dano;*/
	bool operada;
	int oxigenio;
	vector <Unidade*> unidades;
public:
	Sala(string tipo);
	virtual ~Sala();
	
	virtual string toString()const;
	
	string getTipo() const;
	int getID()const;
	
	int getIntegridade()const;
	void setIntegridade(int valor_integridade);
	
	/*int getDano()const;
	void setDano(int oper_dano);*/

	bool getOperada()const;
	void setOperada(bool valor);

	int getOxigenio()const;
	void reduzOxigenio(int oxig_reduzir);
	
	void adicionar_Unidade(Unidade *unidade_a_adicionar);
	void remover_Unidade(Unidade *unidade_a_remover);

	unsigned int countUnidades()const;
	Unidade *getUnidade(int id_unidade)const;
	Unidade *getUnidadePosicao(int pos_unidade)const;

	virtual void salas_actuar_inicio(Nave *n) {};
	virtual void salas_actuar_fim(Nave *n) {};

	void unidades_actuar_inicio();
	void unidades_actuar_fim();

};

class SalaPropulsor : public Sala {
public:
	SalaPropulsor(string tipo);
	void salas_actuar_fim(Nave *n);
};

class SaladeMaquinas : public Sala {
public:
	SaladeMaquinas(string tipo);
};

class SalaSuportedeVida : public Sala {
public:
	SalaSuportedeVida(string tipo);
};

class SalaControlodeEscudo : public Sala {
public:
	SalaControlodeEscudo(string tipo);
};

class SalaPonte : public Sala {
public:
	SalaPonte(string tipo);
};

class SalaBeliche : public Sala {
public:
	SalaBeliche(string tipo);
};

class SalaRaioLaser : public Sala {
public:
	SalaRaioLaser(string tipo);
};

class SalaAutoReparador : public Sala {
public:
	SalaAutoReparador(string tipo);
	void salas_actuar_fim(Nave * n);
};

class SalaSistemadeSegInterno : public Sala {
public:
	SalaSistemadeSegInterno(string tipo);
};

class SalaEnfermaria : public Sala {
public:
	SalaEnfermaria(string tipo);
	void salas_actuar_fim(Nave *n);
};

class SalaArmas : public Sala {
public:
	SalaArmas(string tipo);
};

class SalaAlojamentosdoCapitao : public Sala {
public:
	SalaAlojamentosdoCapitao(string tipo);
};

class SalaOficinaRobotica : public Sala {
public:
	SalaOficinaRobotica(string tipo);
};
