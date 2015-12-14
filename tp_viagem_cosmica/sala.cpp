#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "sala.h"
#include "unidade.h"

Sala::Sala(string tipo, int id_sala):tipo(tipo), id_sala(id_sala) {
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

void Sala::setIntegridade(int valor_integridade) {
	integridade = valor_integridade;
}

int Sala::getOxigenio() const
{
	return oxigenio;
}

string Sala::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
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

void SalaPropulsor::setPropulsao(){
	dist_propulsao = getIntegridade();
}

SaladeMaquinas::SaladeMaquinas(string tipo, int id_sala):Sala(tipo, id_sala) {
	cout << "Sala de Maquinas adicionada" << endl;
}

SalaSuportedeVida::SalaSuportedeVida(string tipo, int id_sala):Sala(tipo, id_sala) {}

SalaControlodeEscudo::SalaControlodeEscudo(string tipo, int id_sala):Sala(tipo, id_sala) {}

SalaPonte::SalaPonte(string tipo, int id_sala):Sala(tipo, id_sala){}

// SALAS OPCIONAIS 
SalaPropulsoresAdicionais::SalaPropulsoresAdicionais(string tipo, int id_sala):Sala(tipo, id_sala), cap_propulsao(100){
	//O jogador pode optar por instalar mais propulsores(idênticos aos 
	//dois propulsores obrigatórios), de forma a garantir que a nave se 
	//pode deslocar mais depressa.
	cout << "Propulsor Adicional adicionado" << endl;
}

int SalaPropulsoresAdicionais::getPropulsao() const
{
	return cap_propulsao;
}

void SalaPropulsoresAdicionais::setPropulsao() {
	cap_propulsao = getIntegridade();
}

SalaBeliche::SalaBeliche(string tipo, int id_sala) : Sala(tipo, id_sala) {
	//A instalação de beliches adicionais permite aumentar o número de 
	//tripulantes. Cada sala de beliches instalada na nave permite trazer 
	//mais um membro da tripulação.Danos ao beliche durante a viagem não 
	//têm consequências(a não ser a perda de jogo, caso seja destruido)
	cout << "Beliche adicionado" << endl;
}


