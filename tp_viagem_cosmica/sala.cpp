#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "sala.h"

Sala::Sala(string tipo, int id_sala) :tipo(tipo), id_sala(id_sala) {
	this->integridade = 100;
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

// SALAS PREDEFINIDAS
SalaPropulsor::SalaPropulsor(string tipo, int id_sala, int propulsao):Sala(tipo, id_sala), dist_propulsao(propulsao){
	cout << "Propulsor adicionado" << endl;
}

int SalaPropulsor::getPropulsao() const
{
	return dist_propulsao;
}

SaladeMaquinas::SaladeMaquinas(string tipo, int id_sala):Sala(tipo, id_sala) {}

SalaSuportedeVida::SalaSuportedeVida(string tipo, int id_sala):Sala(tipo, id_sala) {}

SalaControlodeEscudo::SalaControlodeEscudo(string tipo, int id_sala):Sala(tipo, id_sala) {}

SalaPonte::SalaPonte(string tipo, int id_sala):Sala(tipo, id_sala){}

// SALAS OPCIONAIS 
PropulsoresAdicionais::PropulsoresAdicionais(string tipo, int id_sala):Sala(tipo, id_sala){
	//O jogador pode optar por instalar mais propulsores(idênticos aos 
	//dois propulsores obrigatórios), de forma a garantir que a nave se 
	//pode deslocar mais depressa.
}

SalaBeliche::SalaBeliche(string tipo, int id_sala) : Sala(tipo, id_sala) {
	//A instalação de beliches adicionais permite aumentar o número de 
	//tripulantes. Cada sala de beliches instalada na nave permite trazer 
	//mais um membro da tripulação.Danos ao beliche durante a viagem não 
	//têm consequências(a não ser a perda de jogo, caso seja destruido)
}


