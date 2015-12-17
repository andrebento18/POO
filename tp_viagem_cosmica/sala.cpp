#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "sala.h"

int Sala::conta = 1;

Sala::Sala(string tipo):tipo(tipo){
	id_sala = conta++;
	integridade = 100;
	operada = false;
	oxigenio = 100;
	cout << "Sala " << this->tipo << " criada" << endl;
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

bool Sala::getOperada()const {
	return operada;
}

void Sala::setOperada(bool valor) {
	if (operada != valor)
		operada = valor;
}

int Sala::getOxigenio() const
{
	return oxigenio;
}

void Sala::reduzOxigenio(int oxig_reduzir) {
	oxigenio -= oxig_reduzir;
}

string Sala::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade() << ", " << getOxigenio();
	return os.str();
}

void Sala::adicionar_Unidade(Unidade  *unidade_a_adicionar) {
	if (unidade_a_adicionar->getOndeEstou() == NULL) {	//Verifica se n�o est� em lado nenhum(NULL)
		unidades.push_back(unidade_a_adicionar);
	}else
		cout << "[WARNING]Erro[WARNING]\n";
}

//Unidade* Sala::getUnidades()const {
//	for (auto p = unidades.begin(); p < unidades.end(); p++) {
//		
//	}
//}

////////// SALAS PREDEFINIDAS ///////////
// Sala Propulsor
SalaPropulsor::SalaPropulsor(string tipo, int propulsao):Sala(tipo){
	setPropulsao(propulsao);
	cout << "Propulsor adicionado" << endl;
}

//int SalaPropulsor::getPropulsao() const
//{
//	return dist_propulsao;
//}
//
//void SalaPropulsor::setPropulsao(){
//	dist_propulsao = getIntegridade();
//}

string SalaPropulsor::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}
// Sala de M�quinas
SaladeMaquinas::SaladeMaquinas(string tipo):Sala(tipo) {
	cout << "Sala de Maquinas adicionada" << endl;
}

string SaladeMaquinas::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}
// Sala Suporte de Vida
SalaSuportedeVida::SalaSuportedeVida(string tipo):Sala(tipo) {
	cout << "Sala Suporte de Vida adicionada" << endl;
}

string SalaSuportedeVida::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}
// Sala Controlo de Escudo
SalaControlodeEscudo::SalaControlodeEscudo(string tipo):Sala(tipo) {
	cout << "Sala Controlo de Escudo adicionada" << endl;
}

string SalaControlodeEscudo::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}
// Sala Ponte
SalaPonte::SalaPonte(string tipo):Sala(tipo){
	cout << "Ponte adicionada" << endl;
}

void SalaPonte::setOperada() {
}

int Sala::getUnidades()const {
	return unidades.size();
}

Unidade* Sala::getUnidade(int id)const {
	return unidades[id];
}

string SalaPonte::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}

// Sala Beliche
SalaBeliche::SalaBeliche(string tipo) : Sala(tipo) {
	//A instala��o de beliches adicionais permite aumentar o n�mero de 
	//tripulantes. Cada sala de beliches instalada na nave permite trazer 
	//mais um membro da tripula��o.Danos ao beliche durante a viagem n�o 
	//t�m consequ�ncias(a n�o ser a perda de jogo, caso seja destruido)
	cout << "Beliche adicionado" << endl;
}

string SalaBeliche::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}
// Sala Raio Laser
SalaRaioLaser::SalaRaioLaser(string tipo) :Sala(tipo) {
	cout << "Raio Laser adicionado" << endl;
}

string SalaRaioLaser::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
	return os.str();
}
// Sala Auto Reparador
SalaAutoReparador::SalaAutoReparador(string tipo):Sala(tipo) {
	cout << "Auto-Reparador adicionado" << endl;
}

string SalaAutoReparador::toString()const{
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
	return os.str();
}

SalaSistemadeSegInterno::SalaSistemadeSegInterno(string tipo):Sala(tipo){
	cout << "Sistema de Seguranca Interno adicionado" << endl;
}

string SalaSistemadeSegInterno::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
	return os.str();
}

SalaEnfermaria::SalaEnfermaria(string tipo):Sala(tipo){
	cout << "Enfermaria adicionada" << endl;
}

string SalaEnfermaria::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
	return os.str();
}

SalaArmas::SalaArmas(string tipo):Sala(tipo){
	cout << "Sala de Armas adicionada" << endl;
}

string SalaArmas::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
	return os.str();
}

SalaAlojamentosdoCapitao::SalaAlojamentosdoCapitao(string tipo):Sala(tipo){
	cout << "Alojamento do Capitao adicionado" << endl;
}

string SalaAlojamentosdoCapitao::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
	return os.str();
}

SalaOficinaRobotica::SalaOficinaRobotica(string tipo):Sala(tipo){
	cout << "Oficina de Robotica adicionada" << endl;
}

string SalaOficinaRobotica::toString()const {
	ostringstream os;
	os << "Tipo: " << getTipo() << ", id " << getID() << ", " << getIntegridade();
	return os.str();
}