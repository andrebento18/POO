#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "sala.h"

Sala::Sala(string tipo, int id_sala) :tipo(tipo), id_sala(id_sala) {
	cout << "Sala " << this->tipo << " criada" << endl;
	//falta inicializar integrigade, etc...
}

Sala::~Sala() {
	cout << "Sala " << this->tipo << ", posicao " << this->id_sala << " destruida" << endl;
}

string Sala::getTipo()const {
	return tipo;
}

int Sala::getID()const {
	return id_sala;
}

int Sala::getIntegridade() const
{
	return integridade;
}

int Sala::getOxigenio() const
{
	return oxigenio;
}

string Sala::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID();
	return os.str();
}

SalaPropulsor::SalaPropulsor(string tipo, int id_sala, int propulsao):Sala(tipo, id_sala), dist_propulsao(propulsao){
	cout << "Propulsor adicionado" << endl;
}

int SalaPropulsor::getPropulsao() const
{
	return dist_propulsao;
}

