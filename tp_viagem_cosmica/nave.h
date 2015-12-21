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
	
	Sala *getSala(int id_sala)const;
	string getSalas()const;

	void inicio_turno();
	void check_mov_sala(int id_unidade, string comando_direcao);
	void avancaNave();
	void evento();
};