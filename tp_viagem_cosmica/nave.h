#pragma once
#include "sala.h"
class Nave {
	Sala *salas[3][5];
	int distancia = 0;
public:
	Nave();
	~Nave();
	
	int verifica_saudeNave()const;
	int countTripulacao();

	int getDistancia()const;
	void setDistancia(int dist_somar);
	
	Sala *getSala(int id_sala);
	string getSalas()const;

	void inicio_turno();
	void fim_turno();

	bool check_mov_sala(int id_unidade, string comando_direcao);

	void evento();
};