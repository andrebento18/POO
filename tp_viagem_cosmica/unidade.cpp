#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "caracteristicas.h"
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

string Unidade::getNome() const
{
	return nome;
}

int Unidade::getPV()const {
	return ponto_vida;
}

//void Unidade::LevaDano(int dano_recebido)
//{
//	ponto_vida -= dano_recebido;
//}

Sala * Unidade::getOndeEstou() const
{
	return ondestou;
}

void Unidade::setOndeEstou(Sala * a)
{
	ondestou = a;
}

//Caracteristica *Unidade::getCaracteristica()const {
//
//}

void Unidade::setCaracteristica(Caracteristica *p) {
	vect_car.push_back(p);
}

void Unidade::actua(){
	for (unsigned int i = 0; i < vect_car.size(); i++) {
		vect_car[i]->Actua(this);
	}
}

MembroTripulacao::MembroTripulacao(string tipo):Unidade(tipo, 5){
	Caracteristica *p = new Respira();
	setCaracteristica(p);
	cout << "Membro de Tripulacao criado" << endl;
}

string MembroTripulacao::toString() const{
	ostringstream os;
	os << Unidade::toString(); //<< " , respiracao " << getRespira();
	return os.str();
}

Capitao::Capitao(string tipo) : Unidade(tipo, 6) {
	
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



