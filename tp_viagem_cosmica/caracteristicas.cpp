#include <iostream>

using namespace std;

#include "caracteristicas.h"

Caracteristica::Caracteristica(string tipo) {
	this->tipo = tipo;
}

Caracteristica::~Caracteristica(){
	cout << "Caracteristica eliminada" << endl;
}

string Caracteristica::getTipoCaracterisca(){
	return tipo;
}

Respira::Respira(void) :Caracteristica("Respira") {
	respira = 2;
	cout << "Esta unidade respira" << endl;
}

void Respira::actua_car_inicio(Unidade * u, Nave *n){
	if (u->getOndeEstou()->getOxigenio() <= 0)
		u->LevaDano(1);
	else
		u->getOndeEstou()->reduzOxigenio(respira);
}

Flamejante::Flamejante(void) :Caracteristica("Flamejante") {
	cout << "Esta unidade esta envolta em chamas" << endl;
}

void Flamejante::actua_car_inicio(Unidade * u, Nave * n){
	u->getOndeEstou()->reduzOxigenio(5);
}

Toxico::Toxico(int nvl_toxicd) :Caracteristica("Toxico"), dano_toxico(nvl_toxicd) {
	cout << "Este ser e toxico" << endl;
}

void Toxico::actua_car_inicio(Unidade * u, Nave * n){
	Sala *p = u->getOndeEstou();
	for (unsigned int i = 0; i < p->countUnidades(); i++) {
		bool unidade_toxica = false;
		// Verifica se a unidade a provocar dano é tóxica
		for (unsigned int j = 0; j < p->getUnidadePosicao(i)->countCaracteristicas(); j++) {
			if (p->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca() == "Toxico") {
				unidade_toxica = true;
				break;
			}
		}
		// Se for toxica
		if (unidade_toxica != true) {
			p->getUnidadePosicao(i)->LevaDano(dano_toxico);
		}
	}
}

Indeciso::Indeciso(void):Caracteristica("Indeciso") {
	ignora_actua_inicio = false;
}

void Indeciso::actua_car_inicio(Unidade * u, Nave * n){
	int x = random(1, 2);

	if (x == 1 && ignora_actua_inicio == false) {
		ignora_actua_inicio = true;
	}
	else if (ignora_actua_inicio == true) {
		ignora_actua_inicio = false;
	}
}

void Indeciso::actua_car_fim(Unidade * u, Nave * n){
	if (ignora_actua_inicio == true) {
		u->setOndeEstou(u->getOndeEstava());
	}
}
