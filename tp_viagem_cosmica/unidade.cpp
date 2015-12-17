#include <iostream>
#include <string>
using namespace std;

#include "unidade.h"

Unidade::Unidade(string tipo, int pv) {
	nome = tipo;
	ponto_vida = pv;
	ondestou = NULL;
}

Unidade::~Unidade() {
	cout << "Unidade destruida" << endl;
}

int Unidade::getPV()const {
	return ponto_vida;
}

void Unidade::LevaDano(int dano_recebido)
{
	ponto_vida = ponto_vida - dano_recebido;
}

void Unidade::setRespira(bool respira) {
	this->respira = respira;
}

Sala * Unidade::LocalizarSala() const
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
	/*respira = true;
	reparador = 1;
	combatente = 1;
	operador = true;
	tripulacao = true;*/
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



