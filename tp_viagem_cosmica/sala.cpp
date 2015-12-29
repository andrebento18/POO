#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "sala.h"
#include "nave.h"

int random(int min, int max);

int Sala::conta_salas = 1;

Sala::Sala(string tipo):tipo(tipo){
	id_sala = conta_salas++;
	integridade = 100;
	//dano = 0;
	operada = false;
	oxigenio = 100;
	fogo = false;
	brecha = false;
	curto_circuito = false;
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
	if (getIntegridade() + valor_integridade > 100)
		integridade = 100;
	else
		integridade = valor_integridade;

	if (getIntegridade() == 100) {
		setFogo(false);
		setBrecha(false);
		setCurtoCircuito(false);
	}
}

void Sala::reduzIntegridade(int valor_reduzir){
	if (getIntegridade() - valor_reduzir < 0)
		integridade = 0;
	else
		integridade -= valor_reduzir;
}

//int Sala::getDano() const
//{
//	return 0;
//}
//
//void Sala::setDano(int oper_dano) {
//	if (oper_dano >= 0)
//		dano += oper_dano;
//	else
//		dano -= oper_dano;
//}

bool Sala::getOperada()const {
	return operada;
}

void Sala::setOperada(bool valor) {
	if (valor == true && getIntegridade() == 100)
		operada = true;
	else
		operada = false;
}

int Sala::getOxigenio() const
{
	return oxigenio;
}

void Sala::aumentaOxigenio(int oxig_aumentar){
	if (getOxigenio() + oxig_aumentar > 100)
		oxigenio = 100;
	else
		oxigenio += oxig_aumentar;
}

void Sala::reduzOxigenio(int oxig_reduzir) {
	if (getOxigenio() - oxig_reduzir < 0) {
		oxigenio = 0;
		setFogo(false); // Sem oxig. não há fogo
	}
	else
		oxigenio -= oxig_reduzir;
}

bool Sala::getFogo() const{
	return fogo;
}

void Sala::setFogo(bool valor){
	if (valor == true && getOxigenio() != 0) {
		fogo = true;
	}
	else
		fogo = false;
}

bool Sala::getBrecha() const{
	return brecha;
}

void Sala::setBrecha(bool valor){
	if (valor == true) {
		brecha = true;
		reduzOxigenio(100);
	}
	else
		brecha = false;
}

bool Sala::getCurtoCircuito() const{
	return curto_circuito;
}

void Sala::setCurtoCircuito(bool valor){
	if (valor == true) {
		curto_circuito = true;
	}
	else
		curto_circuito = false;
}

string Sala::toString()const {
	ostringstream os;
	os << "Sala: " << getID() << "   " << getTipo() << ", intg " << getIntegridade() << ", oxig " << getOxigenio() << endl;
	if (unidades.size() != 0) {
		for (unsigned int i = 0; i < unidades.size(); i++)
			os << "\t->" << unidades[i]->getNome() << ", id " << unidades[i]->getID_Unidade() << ", pv " << unidades[i]->getPV() << endl;
	}
	else
		os << "\t->Sala sem unidades" << endl;
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

void Sala::salas_actuar_inicio(Nave *n) {
	// Dano causado pelo Fogo às Unidades na sala
	if (getFogo() == true) {
		for (unsigned int i = 0; i < unidades.size(); i++) {
			unidades[i]->LevaDano(2);
		}
	}
}

void Sala::salas_actuar_fim(Nave *n) {
	// Fogo
	if (getFogo() == true) {
		// Dano causado pelo Fogo à sala
		if (random(1, 2) == 1) {
			reduzIntegridade(10);
		}
		// Norte sul este oeste
		// Dano causado pelo Fogo às salas adjacentes
		// ?????????????????????????????????????????????????????????????????????????????????????????????????????????
	}

	// Curto-circuito
	if (getCurtoCircuito() == true) {
		if (random(1, 4) == 1) {
			for (unsigned int i = 0; i < unidades.size(); i++) {
				unidades[i]->LevaDano(1 * unidades.size());
			}
		}
	}

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

	for (unsigned int i = 0; i < unidades.size(); i++) {
		if (unidades[i]->getOndeEstava() != NULL) {
			unidades[i]->setOndeEstava(NULL);
		}
	}
}

Unidade * Sala::getUnidadePosicao(int posicao) const
{
	return unidades[posicao];
}

////////// SALAS PREDEFINIDAS ///////////

SalaPropulsor::SalaPropulsor(string tipo):Sala(tipo){
	cout << "Propulsor Adicional adicionado" << endl;
}

void SalaPropulsor::salas_actuar_fim(Nave *n) {
	if(n->getSala(5)->getIntegridade() == 100 && n->getSala(8)->getOperada() == true)
		n->setDistancia(getIntegridade());
}

SaladeMaquinas::SaladeMaquinas(string tipo):Sala(tipo) {
	cout << "Sala de Maquinas adicionada" << endl;
}

SalaSuportedeVida::SalaSuportedeVida(string tipo):Sala(tipo) {
	cout << "Sala Suporte de Vida adicionada" << endl;
}

void SalaSuportedeVida::salas_actuar_fim(Nave * n) {
	if (getIntegridade() == 100)
		for (int i = 1; i <= 12; i++) {
			if (n->getSala(i)->getBrecha() == false)
				n->getSala(i)->aumentaOxigenio(2);
			else
				n->getSala(i)->reduzOxigenio(n->getSala(i)->getOxigenio());
		}
}

SalaControlodeEscudo::SalaControlodeEscudo(string tipo):Sala(tipo) {
	cout << "Sala Controlo de Escudo adicionada" << endl;
	escudo = 100;
}

void SalaControlodeEscudo::salas_actuar_fim(Nave * n){
	if (getOperada() == true)
		escudo += 5;
}

int SalaControlodeEscudo::getEscudo() const{
	return escudo;
}

void SalaControlodeEscudo::reduzEscudo(int val_reduzir){
	if (escudo - val_reduzir < 0)
		escudo = 0;
	else
		escudo -= val_reduzir;
}

SalaPonte::SalaPonte(string tipo):Sala(tipo){
	cout << "Ponte adicionada" << endl;
}

SalaBeliche::SalaBeliche(string tipo) : Sala(tipo) {
	cout << "Beliche adicionado" << endl;
}

SalaRaioLaser::SalaRaioLaser(string tipo) :Sala(tipo) {
	cout << "Raio Laser adicionado" << endl;
}

SalaAutoReparador::SalaAutoReparador(string tipo):Sala(tipo) {
	cout << "Auto-Reparador adicionado" << endl;
}

void SalaAutoReparador::salas_actuar_fim(Nave *n) {
	if (getIntegridade() == 100) {
		Sala *s = n->getSala(getID());
		if ((s + 5) != NULL) {
			if ((s++)->getIntegridade() <= 95)
				(s++)->setIntegridade((s++)->getIntegridade() + 5);
		}
		else if ((s + 5) != NULL) {
			if ((s--)->getIntegridade() <= 95)
				(s--)->setIntegridade((s++)->getIntegridade() + 5);
		}
		else if ((s + 5) != NULL) {
			if ((s + 5)->getIntegridade() <= 95)
				(s + 5)->setIntegridade((s++)->getIntegridade() + 5);
		}
		else if ((s - 5) != NULL) {
			if((s-5)->getIntegridade() <= 95)
				(s-5)->setIntegridade((s++)->getIntegridade() + 5);
		}
		cout << "Salas reparadas usando o Auto-Reparador" << endl;
	}
}

SalaSistemadeSegInterno::SalaSistemadeSegInterno(string tipo):Sala(tipo){
	cout << "Sistema de Seguranca Interno adicionado" << endl;
}

SalaEnfermaria::SalaEnfermaria(string tipo):Sala(tipo){
	cout << "Enfermaria adicionada" << endl;
}

void SalaEnfermaria::salas_actuar_fim(Nave * n){
	// VERIFICAR SE É TRIPULANTE
	for (unsigned int i = 0; i < countUnidades(); i++)
		getUnidadePosicao(i)->aumentaPV(1);
}

SalaArmas::SalaArmas(string tipo):Sala(tipo){
	cout << "Sala de Armas adicionada" << endl;
}

SalaAlojamentosdoCapitao::SalaAlojamentosdoCapitao(string tipo):Sala(tipo){
	cout << "Alojamento do Capitao adicionado" << endl;
}

SalaOficinaRobotica::SalaOficinaRobotica(string tipo):Sala(tipo){
	cout << "Oficina de Robotica adicionada" << endl;
}