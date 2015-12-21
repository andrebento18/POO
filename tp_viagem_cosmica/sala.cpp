#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "sala.h"
#include "nave.h"
int Sala::conta_salas = 1;

Sala::Sala(string tipo):tipo(tipo){
	id_sala = conta_salas++;
	integridade = 100;
	operada = false;
	oxigenio = 100;
	cout << "Sala " << this->tipo << " criada" << endl;
}

Sala::~Sala() {
	cout << "Sala " << this->tipo << ", posicao " << this->id_sala << " destruida" << endl;
	cout << "...IMPLEMENTAR DESTRUICAO DE UNIDADES" << endl;
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
	if (valor == true && getIntegridade() == 100/*&& unidade fora de combate*/)
		operada = true;
	else
		operada = false;
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
	os << "Tipo: " << getTipo() << ", id " << getID() << ", intg " << getIntegridade() << ", oxig " << getOxigenio() << " Unidades:" << endl;
	for (unsigned int i = 0; i < unidades.size(); i++)
		os << unidades[i]->getNome() << ", id "<< unidades[i]->getID_Unidade() << ", pv " << unidades[i]->getPV() << endl;
	return os.str();
}

void Sala::adicionar_Unidade(Unidade *unidade_a_adicionar) {
	if (unidade_a_adicionar->getOndeEstou() == NULL) {
		unidades.push_back(unidade_a_adicionar);
		setOperada(true);
	}else
		cout << "[WARNING]Erro[WARNING]\n";
}

void Sala::remover_Unidade(Unidade *unidade_a_remover) {
	if (unidade_a_remover->getOndeEstou() == this) {
		for (auto p = unidades.begin(); p < unidades.end(); p++) {
			if ((*p)->getID_Unidade() == unidade_a_remover->getID_Unidade()) {
				unidades.erase(p);
				break;
			}
		}
		if (unidades.size() == 0)
			setOperada(false);
	}
}

unsigned int Sala::countUnidades()const {
	return unidades.size();
}

Unidade* Sala::getUnidade(int id_unidade)const {
	for (unsigned int i = 0; i < unidades.size(); i++) {
		if (unidades[i]->getID_Unidade() == id_unidade)
			return unidades[i];
	}
	return nullptr;
}

void Sala::unidades_actuar_inicio() {
	for (unsigned int i = 0; i < unidades.size(); i++) {
		unidades[i]->actua_inicio();
	}
}

void Sala::unidades_actuar_fim() {
	for (unsigned int i = 0; i < unidades.size(); i++) {
		unidades[i]->actua_fim();
	}
}

////////// SALAS PREDEFINIDAS ///////////

SalaPropulsor::SalaPropulsor(string tipo):Sala(tipo){
	cout << "Propulsor Adicional adicionado" << endl;
}

void SalaPropulsor::salas_actuar_fim(Nave *n) {
	if(n->getSala(5)->getIntegridade() == 100 /*VER SE PONTE ESTA OPERADA*/)
		n->setDistancia(getIntegridade());
}

string SalaPropulsor::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}
// Sala de Máquinas
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

string SalaPonte::toString()const {
	ostringstream os;
	os << Sala::toString();
	return os.str();
}

// Sala Beliche
SalaBeliche::SalaBeliche(string tipo) : Sala(tipo) {
	//A instalação de beliches adicionais permite aumentar o número de 
	//tripulantes. Cada sala de beliches instalada na nave permite trazer 
	//mais um membro da tripulação.Danos ao beliche durante a viagem não 
	//têm consequências(a não ser a perda de jogo, caso seja destruido)
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