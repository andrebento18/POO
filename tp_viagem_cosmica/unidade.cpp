#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "caracteristicas.h"
#include "unidade.h"
#include "sala.h"

int Unidade::conta_unidades = 0;
int Unidade::ponto_vida_inicial = 0;

Unidade::Unidade(string tipo, int pv) {
	id_unidade = conta_unidades++;
	nome = tipo;
	ponto_vida = pv;
	ponto_vida_inicial = pv;
	ondestou = NULL;
	ondestava = NULL;
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

string Unidade::getNome() const{
	return nome;
}

int Unidade::getPV()const {
	return ponto_vida;
}

int Unidade::getPVInicial()const {
	return ponto_vida_inicial;
}

void Unidade::setPV(int new_ponto_vida) {
	if (new_ponto_vida >= 0)
		ponto_vida += new_ponto_vida;
	else
		ponto_vida -= new_ponto_vida;
}

void Unidade::aumentaPV(int valor_aumentar){
	if (ponto_vida + valor_aumentar > ponto_vida_inicial) {
		ponto_vida = ponto_vida_inicial;
	}
	else
		ponto_vida += valor_aumentar;
}

void Unidade::LevaDano(int dano_recebido){
	if (getPV() == 0 || getPV() < 0) 
		getOndeEstou()->remover_Unidade(this);
	else {
		ponto_vida -= dano_recebido;
		if (getPV() == 0 || getPV() < 0)
			getOndeEstou()->remover_Unidade(this);
	}
}

Sala * Unidade::getOndeEstou()const{
	return ondestou;
}

Sala * Unidade::getOndeEstava()const{
	return ondestava;
}

void Unidade::setOndeEstou(Sala *s){
	ondestou = s;
}

void Unidade::setOndeEstava(Sala *s) {
	ondestava = s;
}

void Unidade::mover_unidade(int id_unidade, Sala *sala_antiga, Sala *sala_nova) {
	this->setOndeEstava(sala_antiga);
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

Caracteristica * Unidade::getCaracteristicaPosicao(int posicao)
{
	return vect_car[posicao];
}

unsigned int Unidade::countCaracteristicas() const
{
	return vect_car.size();
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
	cout << endl << tipo << " criado" << endl;
	setCaracteristica(new Respira());
	setCaracteristica(new Reparador(1));
	setCaracteristica(new Combatente(1));
	setCaracteristica(new Operador());
	setCaracteristica(new Tripulacao());
}

Capitao::Capitao(string tipo) : Unidade(tipo, 6) {
	cout << endl << tipo << " criado" << endl;
	setCaracteristica(new Respira());
	//exoesqueleto = 1; //mete o exosqueleto com o valor a ser ignorado
	setCaracteristica(new Combatente(2));
	setCaracteristica(new Operador());
	setCaracteristica(new Tripulacao());
}

Robot::Robot(string tipo) : Unidade(tipo, 8) {
	cout << endl << tipo << " criado" << endl;
	//exoesqueleto = 2;//mete o exosqueleto com o valor a ser ignorado
	setCaracteristica(new Combatente(3));
	setCaracteristica(new Tripulacao());
}

Pirata::Pirata(string tipo) :Unidade(tipo, 4) {
	cout << tipo << " criado" << endl;
	setCaracteristica(new Respira());
	//Inimigo(1, 2), Move(15)
}

Geigermorfo::Geigermorfo(string tipo) :Unidade(tipo, 4) {
	cout << tipo << " criado" << endl;
	//Caracter�sticas: Xenomorfo(3), Misterioso, Move(50), Casulo(20), Exoesqueleto(3).
}

CasulodeGeigermorfo::CasulodeGeigermorfo(string tipo):Unidade(tipo, 6){
	cout << tipo << " criado" << endl;
	//Caracter�sticas: Xenomorfo(0), Exoesqueleto(1)
}

Blob::Blob(string tipo):Unidade(tipo, 8){
	cout << tipo << " criado" << endl;
	//Caracter�sticas: Xenomorfo(0), Regenerador(2), Flamejante, Toxico, Reparador(6), operador, Move(15).
}

Mxyzypykwi::Mxyzypykwi(string tipo):Unidade(tipo, 8){
	cout << tipo << " criado" << endl;
	//Caracter�sticas: Xenomorfo(0), Hipnotizador(15), Move(30), Mutatis Mutandis(10)
	setCaracteristica(new Respira());
}
