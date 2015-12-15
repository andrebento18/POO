#pragma once
#include "sala.h"
class Nave {
	Sala *salas[3][5];
	int distancia = 0; // Distância percorrida
public:
	Nave();
	~Nave();
	int verifica_saudeNave()const;
	int getDistancia()const;
	void setDistancia();
	void evento();
	//Sala *mover_para_sala(string comando_direcao, int id);
	string getSalas()const;
	void setReparacao();
};