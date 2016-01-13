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
	cout << "Unidade " << getNome() << ", " << getID_Unidade() <<  " destruida" << endl;
	for (unsigned int i = 0; i < vect_car.size(); i++)
		delete vect_car[i];
}

string Unidade::toString() {
	ostringstream os;
	if(getCaracteristicaTipo("Exoesqueleto") != NULL)
		os << "Unidade " << getNome() << ", id: " << getID_Unidade() + 1 << ", pv: " << getPV() << ", exoesq: " << getCaracteristicaTipo("Exoesqueleto")->getExoesqueleto();
	else
		os << "Unidade " << getNome() << ", id: " << getID_Unidade() + 1 << ", pv: " << getPV();
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
	ponto_vida = new_ponto_vida;
}

void Unidade::aumentaPV(int valor_aumentar){
	if (ponto_vida + valor_aumentar > ponto_vida_inicial) {
		ponto_vida = ponto_vida_inicial;
	}
	else
		ponto_vida += valor_aumentar;
}

void Unidade::LevaDano(int dano_recebido){
	ponto_vida -= dano_recebido;
	if (getPV() <= 0) {
		getOndeEstou()->remover_Unidade(this);
		cout << "Unidade " << getNome() << ", " << getID_Unidade() << " ficou com " << getPV() << endl;
		system("pause");
	}
}

int Unidade::getID_Unidade() const{
		return id_unidade;
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
}

void Unidade::setCaracteristica(Caracteristica *p) {
	vect_car.push_back(p);
}

Caracteristica *Unidade::getCaracteristica(Caracteristica *p) {
	if (!p)
		return p;
	else
		return nullptr;
}

Caracteristica * Unidade::getCaracteristicaPosicao(int posicao){
	return vect_car[posicao];
}

Caracteristica * Unidade::getCaracteristicaTipo(string tipo){
	for (unsigned int i = 0; i < vect_car.size(); i++)
		if (vect_car[i]->getTipoCaracterisca() == tipo)
			return vect_car[i];
	return nullptr;
}

unsigned int Unidade::countCaracteristicas() const{
	return (unsigned)vect_car.size();
}

void Unidade::actua_inicio(Nave *n){
	for (unsigned int i = 0; i < vect_car.size(); i++)
		vect_car[i]->actua_car_inicio(this, n);
}

void Unidade::actua_fim(Nave *n) {
	for (unsigned int i = 0; i < vect_car.size(); i++) 
		vect_car[i]->actua_car_fim(this, n);
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
	setCaracteristica(new Exoesqueleto(1));
	setCaracteristica(new Combatente(2));
	setCaracteristica(new Operador());
	setCaracteristica(new Tripulacao());

	setCaracteristica(new Mutantis_Mutandis(90));
	setCaracteristica(new Casulo(90));
}

Robot::Robot(string tipo) : Unidade(tipo, 8) {
	cout << endl << tipo << " criado" << endl;
	setCaracteristica(new Exoesqueleto(2));
	setCaracteristica(new Combatente(3));
	setCaracteristica(new Tripulacao());
}

Pirata::Pirata(string tipo) :Unidade(tipo, 4) {
	cout << tipo << " criado" << endl;
	setCaracteristica(new Respira());
	setCaracteristica(new Inimigo(1, 2));
	setCaracteristica(new Move(15));
}

Geigermorfo::Geigermorfo(string tipo) :Unidade(tipo, 4) {
	cout << tipo << " criado" << endl;
	setCaracteristica(new Xenomorfo(3));
	setCaracteristica(new Misterioso());
	setCaracteristica(new Move(50));
	setCaracteristica(new Casulo(20));
	setCaracteristica(new Exoesqueleto(3));
}

CasulodeGeigermorfo::CasulodeGeigermorfo(string tipo, Unidade *u):Unidade(tipo, 6){
	cout << tipo << " criado" << endl;
	setCaracteristica(new Xenomorfo(0));
	setCaracteristica(new Exoesqueleto(1));
	// Aprisionar a unidade
	unidade_aprisionada = u;
	// Set localização do Casulo na mesma sala da unidade
	u->getOndeEstou()->adicionar_Unidade(this);
	// Remover a unidade da sala
	u->getOndeEstou()->remover_Unidade(u);
}

void CasulodeGeigermorfo::actua_unidade_incio(Nave * n){
	if (turno == 3) {
		Unidade *p = new Geigermorfo("Geigermorfo");
		getOndeEstou()->adicionar_Unidade(p);
		getOndeEstou()->remover_Unidade(this);
	}
	else
		turno++;
}

void CasulodeGeigermorfo::actua_unidade_fim(Nave *n) {
	if (getPV() <= 0) {
		getOndeEstou()->adicionar_Unidade(unidade_aprisionada);
		cout << "????????????????" << unidade_aprisionada->getID_Unidade();
		system("pause");
	}
}

Blob::Blob(string tipo):Unidade(tipo, 8){
	cout << tipo << " criado" << endl;
	setCaracteristica(new Xenomorfo(0));
	setCaracteristica(new Regenerador(2));
	setCaracteristica(new Flamejante());
	setCaracteristica(new Toxico(2)); // NAO DIZ NADA NO ENUNCIADO SOBRE A TOXICIDADE DO BLOB QUANTO É ??????????
	setCaracteristica(new Reparador(6));
	setCaracteristica(new Operador());
	setCaracteristica(new Move(15));
}

Mxyzypykwi::Mxyzypykwi(string tipo):Unidade(tipo, 8){
	cout << tipo << " criado" << endl;
	setCaracteristica(new Xenomorfo(0));
	setCaracteristica(new Hipnotizador(15));
	setCaracteristica(new Move(30));
	setCaracteristica(new Mutantis_Mutandis(10));
	setCaracteristica(new Respira());
}
