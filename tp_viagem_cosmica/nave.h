#pragma once
#include "sala.h"
class Nave {
	string nome;
	Sala *salas[3][5];
	int distancia; // Distância percorrida
public:
	int contador = 0;
	Nave();
	~Nave();
	int verifica_saudeNave()const;
	int getDistancia()const;
	void setDistancia(int dist_somar);
	string getSalas()const;
};