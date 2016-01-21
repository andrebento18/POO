#pragma once
#include "unidade.h"

class Nave;
class Sala {
	string tipo;
	int id_sala;
	static int conta_salas;
	int integridade;
	bool operada;
	int oxigenio;
	bool fogo;
	bool brecha;
	bool curto_circuito;
	vector <Unidade*> unidades;
	vector <Unidade*> piratas;
	vector <Unidade*> xenomorfos;
public:
	Sala(string tipo);
	Sala(const Sala *s);
	virtual ~Sala();
	
	virtual string toString()const;
	
	string getTipo() const;
	int getID()const;
	
	int getIntegridade()const;
	void setIntegridade(int valor_integridade);
	void aumentaIntergridade(int valor_aumentar);
	void reduzIntegridade(int valor_reduzir);
	
	/*int getDano()const;
	void setDano(int oper_dano);*/

	bool getOperada()const;
	void setOperada(bool valor);

	int getOxigenio()const;
	void aumentaOxigenio(int oxig_aumentar);
	void reduzOxigenio(int oxig_reduzir);

	bool getFogo()const;
	void setFogo(bool valor);

	bool getBrecha()const;
	void setBrecha(bool valor);

	bool getCurtoCircuito()const;
	void setCurtoCircuito(bool valor);
	
	void adicionar_Unidade(Unidade *unidade_a_adicionar);

	void remover_Unidade(Unidade *unidade_a_remover);
	void mata_Unidade(Unidade *unidade_a_remover);

	int countUnidades()const;
	Unidade *getUnidade(int id_unidade);
	Unidade *getUnidadePosicao(int pos_unidade);

	int countPiratas()const;
	Unidade *getPirata(int id_pirata);
	Unidade *getPirataPosicao(int pos_pirata);

	int countXenomorfo()const;
	Unidade *getXenomorfo(int id_xenomorfo);
	Unidade *getXenomorfoPosicao(int pos_xenomorfo);

	virtual void salas_actuar_inicio(Nave *n);
	virtual void salas_actuar_fim(Nave *n);

	void unidades_actuar_inicio(Nave *n);
	void unidades_actuar_fim(Nave *n);

	virtual int getEscudo()const { return 0; };
	virtual void reduzEscudo(int val_reduzir) {};

	Sala &operator=(Sala *s);
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
	void salas_actuar_fim(Nave *n);
};

class SalaControlodeEscudo : public Sala {
	int escudo;
public:
	SalaControlodeEscudo(string tipo);
	void salas_actuar_fim(Nave *n);
	int getEscudo()const;
	void reduzEscudo(int val_reduzir);
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
	void salas_actuar_fim(Nave * n);
};

class SalaEnfermaria : public Sala {
public:
	SalaEnfermaria(string tipo);
	void salas_actuar_fim(Nave *n);
};

class SalaArmas : public Sala {
public:
	SalaArmas(string tipo);
	void salas_actuar_fim(Nave *n);
};

class SalaAlojamentosdoCapitao : public Sala {
public:
	SalaAlojamentosdoCapitao(string tipo);
};

class SalaOficinaRobotica : public Sala {
public:
	SalaOficinaRobotica(string tipo);
};
