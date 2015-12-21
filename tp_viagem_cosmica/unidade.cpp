#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "caracteristicas.h"
#include "unidade.h"
#include "sala.h"

int Unidade::conta_unidades = 0;

Unidade::Unidade(string tipo, int pv) {
	id_unidade = conta_unidades++;
	nome = tipo;
	ponto_vida = pv;
	ondestou = NULL;
}

Unidade::~Unidade() {
	cout << "Unidade " << getNome() << " destruida" << endl;
	cout << "...IMPLEMENTAR APAGAR AS CARS" << endl;
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

void Unidade::LevaDano(int dano_recebido){
	if (getPV() == 0 || getPV() < 0) 
		getOndeEstou()->remover_Unidade(this);
	else
		ponto_vida -= dano_recebido;
}

Sala * Unidade::getOndeEstou()const
{
	return ondestou;
}

void Unidade::setOndeEstou(Sala *s){
	ondestou = s;
}

void Unidade::mover_unidade(int id_unidade, Sala *sala_antiga, Sala *sala_nova) {
	sala_antiga->remover_Unidade(this);
	setOndeEstou(NULL);
	sala_nova->adicionar_Unidade(this);
	setOndeEstou(sala_nova);
	cout << getNome() << ", id " << getID_Unidade() << " movido de " << sala_antiga->getTipo() << ", para " << sala_nova->getTipo() << endl;
}

void Unidade::setCaracteristica(Caracteristica *p) {
	vect_car.push_back(p);
}

Caracteristica *Unidade::getCaracteristica(Caracteristica *p) {
	if (!p)
		return p;
}

void Unidade::actua_inicio(){
	for (unsigned int i = 0; i < vect_car.size(); i++) {
		vect_car[i]->actua_car_inicio(this);
	}
}

void Unidade::actua_fim() {
	for (unsigned int i = 0; i < vect_car.size(); i++) {
		vect_car[i]->actua_car_fim(this);
	}
}

MembroTripulacao::MembroTripulacao(string tipo):Unidade(tipo, 5){
	setCaracteristica(new Respira());
	setCaracteristica(new Reparador(1));
	/*Combatente 
	Operador*/
	setCaracteristica(new Tripulacao());
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



