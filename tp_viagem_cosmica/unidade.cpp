#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "unidade.h"
#include "sala.h"

Unidade::Unidade(string tipo, int pv) {
	nome = tipo;
	ponto_vida = pv;
	ondestou = NULL;
}

Unidade::~Unidade() {
	cout << "Unidade " << getNome() << " destruida" << endl;
}

string Unidade::toString()const {
	ostringstream os;
	os << "Unidade " << getNome() << ", pv: " << getPV();
	return os.str();
}

int Unidade::getPV()const {
	return ponto_vida;
}

void Unidade::LevaDano(int dano_recebido)
{
	ponto_vida -= dano_recebido;
}

Sala * Unidade::getOndeEstou() const
{
	return ondestou;
}

string Unidade::getNome() const
{
	return nome;
}

void Unidade::setOndeEstou(Sala * a)
{
	ondestou = a;
}

Unidade_MembroTripulacao::Unidade_MembroTripulacao(string tipo):Unidade( tipo, 5){
	setRespira(true);
	this->setCaracteristica()->
}

string Unidade_MembroTripulacao::toString() const{
	ostringstream os;
	os << Unidade::toString() << " , respiracao " << getRespira();
	return os.str();
}

void Unidade::actuar()
{
	for (unsigned int i = 0; i < vect_car.size(); i++) {
		vect_car[i]->Actua(this);
	}
}

void Unidade_MembroTripulacao::Respirar() {
	getOndeEstou()->reduzOxigenio(2); // Ver quanto respira
}

Capitao::Capitao(string tipo) : Unidade(tipo, 6) {
	setRespira(true);
	//respira = true;
	//exoesqueleto = 1; //mete o exosqueleto com o valor a ser ignorado
	//combatente = 2;
	//operador = true;
	//tripulacao = true;
}

Robot::Robot(string tipo) : Unidade(tipo, 8) {
	//exoesqueleto = 2;//mete o exosqueleto com o valor a ser ignorado
	//combatente = 3;
	//tripulacao = true;
}



