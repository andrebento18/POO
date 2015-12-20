#pragma once
#include "sala.h"
class Nave {
	Sala *salas[3][5];
	int distancia = 0;
public:
	Nave();
	~Nave();
	
	int verifica_saudeNave()const;
	int getDistancia()const;
	void setDistancia(int dist_somar) {
		distancia += dist_somar;
	};
	//Sala *mover_para_sala(string comando_direcao, int id);
	string getSalas()const;
	void inicio_turno();
	void avancaNave();
	void evento();
};