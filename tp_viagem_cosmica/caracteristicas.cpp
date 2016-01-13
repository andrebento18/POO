#include <iostream>
#include <string>
using namespace std;

#include "caracteristicas.h"

Caracteristica::Caracteristica(string tipo) {
	this->tipo = tipo;
}

Caracteristica::~Caracteristica(){
	cout << "Caracteristica eliminada" << endl;
}

string Caracteristica::getTipoCaracterisca(){
	return tipo;
}

Respira::Respira(void) :Caracteristica("Respira") {
	respira = 2;
	cout << "Esta unidade respira" << endl;
}

void Respira::actua_car_inicio(Unidade * u, Nave *n){
	if (u->getOndeEstou()->getOxigenio() <= 0)
		u->LevaDano(1);
	else
		u->getOndeEstou()->reduzOxigenio(respira);
}

Flamejante::Flamejante(void) :Caracteristica("Flamejante") {
	cout << "Esta unidade esta envolta em chamas" << endl;
}

void Flamejante::actua_car_inicio(Unidade * u, Nave * n){
	u->getOndeEstou()->reduzOxigenio(5);
}

Toxico::Toxico(int nvl_toxicd) :Caracteristica("Toxico"), dano_toxico(nvl_toxicd) {
	cout << "Este ser e toxico" << endl;
}

void Toxico::actua_car_inicio(Unidade * u, Nave * n){
	Sala *p = u->getOndeEstou();
	// Unidades
	for (unsigned int i = 0; i < p->countUnidades(); i++)
		p->getUnidadePosicao(i)->LevaDano(dano_toxico);
	// Piratas
	for (unsigned int i = 0; i < p->countPiratas(); i++)
		p->getPirataPosicao(i)->LevaDano(dano_toxico);
	// Xenomorfos
	for (unsigned int i = 0; i < p->countXenomorfo(); i++) {
		// Verifica se a unidade a provocar dano � t�xica
		if (p->getUnidadePosicao(i)->getCaracteristicaTipo("Toxico") == NULL) 
			p->getUnidadePosicao(i)->LevaDano(dano_toxico);
	}
}

Indeciso::Indeciso(void):Caracteristica("Indeciso") {
	ignora_actua_inicio = false;
}

void Indeciso::actua_car_inicio(Unidade * u, Nave * n){
	int x = random(1, 2);

	if (x == 1 && ignora_actua_inicio == false) {
		ignora_actua_inicio = true;
	}
	else if (ignora_actua_inicio == true) {
		ignora_actua_inicio = false;
	}
}

void Indeciso::actua_car_fim(Unidade * u, Nave * n){
	if (ignora_actua_inicio == true) {
		u->setOndeEstou(u->getOndeEstava());
	}
}

Misterioso::Misterioso(void):Caracteristica("Misterioso") {
	count_turnos = 0;
	cout << "Sou um ser misterioso" << endl;
}

void Misterioso::actua_car_fim(Unidade *u, Nave *n){
	int x = random(1, 4);
	if (x == 1 && count_turnos == 0) {
		count_turnos = 1;
	}
	else if (count_turnos == 1) {
		int sala_escolhida = random(1, 12);
		u->getOndeEstou()->remover_Unidade(u);
		u->mover_unidade(u->getID_Unidade(), u->getOndeEstou(), n->getSala(sala_escolhida));
		int indeciso = random(1, 2);
	}
}

Regenerador::Regenerador(int cap_regenerar):Caracteristica("Regenerador") {
	this->cap_regenerar = cap_regenerar;
	cout << "Este ser e capaz de regenerar " << cap_regenerar << " pontos de vida por turno" << endl;
}

void Regenerador::actua_car_inicio(Unidade *u, Nave *n) {
	u->aumentaPV(cap_regenerar);
}

// FALATA IMPLEMENTAR "BEM" ESTA ????????????????????
Exoesqueleto::Exoesqueleto(int cap_exoesqueleto):Caracteristica("Exoesqueleto") {
	this->cap_exoesqueleto = cap_exoesqueleto;
	cap_exoesqueleto_inicial = cap_exoesqueleto;
	cout << "Esta unidade esta protegida por um exoesqueleto " << this->cap_exoesqueleto << " pontos de capacidade" << endl;
}

void Exoesqueleto::actua_car_inicio(Unidade * u, Nave * n){
	setExoesqueleto(cap_exoesqueleto_inicial);
}

bool Exoesqueleto::verifica_exoesqueleto(Sala *s, int id_unidade) {
	for (unsigned int i = 0; i < s->getUnidade(id_unidade)->countCaracteristicas(); i++) {
			string tipo_car = s->getUnidadePosicao(id_unidade)->getCaracteristicaPosicao(i)->getTipoCaracterisca();
			if (tipo_car == "Exoesqueleto") {
				return true;
			}
	}
	return false;
}

void Exoesqueleto::reduzExoesqueleto(int valor_reduzir) {
	if (cap_exoesqueleto - valor_reduzir <= 0)
		cap_exoesqueleto = 0;
	else
		cap_exoesqueleto -= valor_reduzir;
}

int Exoesqueleto::getExoesqueleto()const {
	return cap_exoesqueleto;
}

void Exoesqueleto::setExoesqueleto(int cap_exoesqueleto){
	this->cap_exoesqueleto = cap_exoesqueleto;
}

void Exoesqueleto::LevaDano(Unidade *u, int dano_recebido){
	if (cap_exoesqueleto - dano_recebido <= 0) {
		cap_exoesqueleto = 0;
		u->LevaDano(dano_recebido - cap_exoesqueleto);
	}
	else {
		cap_exoesqueleto -= dano_recebido;
	}
}
// **********************************************************

// FALTA IMPLEMENTAR O FACTO DE N�O SE PODER MOVER QUANDO ESTA NUMA SALA COM CURTO-CIRCUITO ???????????
Robotico::Robotico(void):Caracteristica("Robotico"){
	cout << "Esta unidade e do tipo robotico" << endl;
}
// ***********************************************

Reparador::Reparador(int cap_reparar) : Caracteristica("Reparador") {
	this->cap_reparar = cap_reparar;
	cout << "Esta unidade repara " << cap_reparar << " pontos, por turno, da sala onde esta" << endl;
}

void Reparador::actua_car_fim(Unidade *u, Nave *n) {
	bool existe_inimigos = false;
	if (u->getOndeEstou()->getTipo() != "Propulsor Adicional" && u->getOndeEstou()->getTipo() != "Propulsor" && u->getOndeEstou()->getIntegridade() < 100) {
		// FALTA VERIFICAR SE A UNDIADE EST� EM COMBATE ?????????????????????????
		/*
		for (unsigned int i = 0; i < u->getOndeEstou()->countUnidades(); i++) {
			for (unsigned int j = 0; j < u->countCaracteristicas(); j++) {
				if (u->getOndeEstou()->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca() != "Tripulacao") {
					existe_inimigos = true;
					cout << "Passei";
				}
			}
		}
		*/
		
		if (existe_inimigos == false)
			u->getOndeEstou()->aumentaIntergridade(cap_reparar);
		if (u->getNome() == "Blob")
			u->getOndeEstou()->aumentaIntergridade(cap_reparar);
	}
}

Combatente::Combatente(int dano_que_causa):Caracteristica("Combatente") {
	this->capacidade_combate = dano_que_causa;
	cout << "Combatente capaz de causar " << capacidade_combate << " pontos de dano" << endl;
}

void Combatente::setCapCombate(int arma){
	capacidade_combate += arma;
}

void Combatente::actua_car_fim(Unidade *u, Nave *n) {
	int	id_inimigo = 0;
	int escolhe_alvo = random(0, 1);

	Sala *s = u->getOndeEstou();

	// Atacar Piratas
	if (s->countPiratas() != 0 && escolhe_alvo == 0) {
		id_inimigo = random(0, s->countPiratas());
		s->getPirata(id_inimigo)->LevaDano(capacidade_combate);
	}
	
	// Atacar Xenomorfos
	if (s->countXenomorfo() != 0 && escolhe_alvo == 1) {
		id_inimigo = random(0, s->countXenomorfo());
		s->getXenomorfo(id_inimigo)->LevaDano(capacidade_combate);
	}
}

Xenomorfo::Xenomorfo(int cap_dano):Caracteristica("Xenomorfo") {
	this->cap_dano = cap_dano;
	cout << "Esta unidade e do tipo Xenomorfo" << endl;
}

void Xenomorfo::actua_car_fim(Unidade *u, Nave *n) {
	int	id_inimigo = 0;
	int escolhe_alvo = random(0, 1);

	Sala *s = u->getOndeEstou();

	// Atacar Unidades
	if (s->countUnidades() != 0 && escolhe_alvo == 0) {
		id_inimigo = random(0, s->countUnidades());
		s->getUnidade(id_inimigo)->LevaDano(cap_dano);
	}

	// Atacar Piratas
	if (s->countPiratas() != 0 && escolhe_alvo == 1) {
		id_inimigo = random(0, s->countPiratas());
		s->getPirata(id_inimigo)->LevaDano(cap_dano);
	}
}

Casulo::Casulo(int prob):Caracteristica("Casulo"), prob_casulo(prob){
	cout << "Esta unidade � capaz de aprisionar os membros da tripulacao" << endl;
}

void Casulo::actua_car_fim(Unidade * u, Nave * n){
	Sala *s = u->getOndeEstou();
	int comeu = 0;

	do {
		int escolhe_alvo = random(0, 1);
		if (escolhe_alvo == 0) {
			// Casulo em Tripulacao
			for (unsigned int i = 0; i < s->countUnidades(); i++) {
				if (random(0, 99) <= prob_casulo) {
					new CasulodeGeigermorfo("Casulo de Geigermorfo", s->getUnidadePosicao(i));
					comeu = 1;
					return;
				}
			}
		}
		else if (escolhe_alvo == 1) {
			for (unsigned int i = 0; i < s->countPiratas(); i++) {
				if (random(0, 99) <= prob_casulo) {
					new CasulodeGeigermorfo("Casulo de Geigermorfo", s->getPirataPosicao(i));
					comeu = 1;
					return;
				}
			}

		}
	} while (comeu == 0);
}


Mutantis_Mutandis::Mutantis_Mutandis(int prob) :Caracteristica("Mutantis_Mutandis") {
	this->prob = prob;
	cout << "Esta unidade � capaz de alterar a sala onde se encontra com " << prob << " % probabilidade" << endl;
}

void Mutantis_Mutandis::actua_car_inicio(Unidade * u, Nave * n){
	if (random(0, 99) <= prob) {
		if (u->getOndeEstou() == n->getSala(2) || u->getOndeEstou() == n->getSala(3) || u->getOndeEstou() == n->getSala(4) || u->getOndeEstou() == n->getSala(10) || u->getOndeEstou() == n->getSala(11) || u->getOndeEstou() == n->getSala(12)) {
			int escolha_sala = random(1, 9);
			Sala *s = NULL;
			switch (escolha_sala) {
				case 1: {
					s = new SalaPropulsor("Propulsor Adicional");
					break; 
				}
				case 2: {
					s = new SalaBeliche("Beliche");
					break;
				}
				case 3: {
					s = new SalaRaioLaser("Raio Laser");
					break;
				}
				case 4: {
					s = new SalaAutoReparador("Auto-reparador");
					break;
				}
				case 5: {
					s = new SalaSistemadeSegInterno("Sistema de Seguranca interno");
					break;
				}
				case 6: {
					s = new SalaEnfermaria("Enfermaria");
					break;
				}
				case 7: {
					s = new SalaArmas("Sala de armas");
					break;
				}
				case 8: {
					s = new SalaAlojamentosdoCapitao("Alojamentos do Capitao");
					break;
				}
				case 9: {
					s = new SalaOficinaRobotica("Oficina Robotica");
					break;
				}
			}
			// PROBLEMAS *********************************************
			*u->getOndeEstou() = s;
			cout << "Sala " << u->getOndeEstou()->getTipo() << " alterada para um " << s->getTipo() << endl;
			cout << s->toString();
			system("pause");
		}
	}
}

Hipnotizador::Hipnotizador(int prob_hip):Caracteristica("Hipnotizador"){
	this->prob_hip = prob_hip;
	cout << "Esta unidade e capaz de hipnotizar outra" << endl;
}

void Hipnotizador::actua_car_inicio(Unidade *u, Nave *n) {
	Sala *s = u->getOndeEstou();
	for (unsigned int i = 0; i < s->countUnidades(); i++) {
		s->getUnidadePosicao(i)->setCaracteristica(new Indeciso());
		break;
	}
}

Operador::Operador(void) :Caracteristica("Operador") {
	cout << "Esta unidade e capaz de operar salas" << endl;
}

// ***************************************************
void Operador::actua_car_inicio(Unidade *u, Nave *n) {
	// FALATA VERIFICAR SE EST� EM COMBATE ???????? (NAO VAI L� S� COM O FACTO DE A SALA NAO ESTAR OPERADA)
	if (u->getOndeEstou()->getIntegridade() == 100)
		u->getOndeEstou()->setOperada(true);
}
// ***************************************************

Tripulacao::Tripulacao(void):Caracteristica("Tripulacao") {
	cout << "Faco parte da tripulacao da nave" << endl;
}

Inimigo::Inimigo(int x, int y):dano_unidade(x), dano_sala(y), Caracteristica("Inimigo") {
	cout << "Esta unidade provoca " << dano_unidade << " pontos de dano a unidades inimigas ou " << dano_sala << " pontos de dano a salas" << endl;
}

void Inimigo::actua_car_inicio(Unidade *u, Nave *n) {
	int	id_inimigo = 0;
	int escolhe_alvo = random(0, 1);

	Sala *s = u->getOndeEstou();

	// Atacar Tripulacao
	if (s->countUnidades() != 0 && escolhe_alvo == 0) {
		id_inimigo = random(0, s->countUnidades());
		s->getUnidade(id_inimigo)->LevaDano(dano_unidade);
	}
	// Atacar Xenomorfos
	else if (s->countXenomorfo() != 0 && escolhe_alvo == 1) {
		id_inimigo = random(0, s->countXenomorfo());
		s->getXenomorfo(id_inimigo)->LevaDano(dano_unidade);
	}
	// N�o existe enimigo
	else
		u->getOndeEstou()->reduzIntegridade(dano_sala);
}

Move::Move(int pmovimento):Caracteristica("Move"), prob_movimento(pmovimento) {
	cout << "Esta unidade pode mover-se para outra sala com prob. " << prob_movimento << " %" << endl;
}

void Move::actua_car_inicio(Unidade *u, Nave *n) {
	if (random(0, 99) < prob_movimento) {
		// Sortear o movimento "cima", "baixo", "esquerda", "direita"
		string comando_direcao;
			switch (random(1, 4)) {
			case 1: comando_direcao = "cima";
				break;
			case 2: comando_direcao = "baixo";
				break;
			case 3: comando_direcao = "esquerda";
				break;
			case 4: comando_direcao = "direita";
				break;
			}
			cout << u->getID_Unidade() << ", " << comando_direcao << endl;
			system("pause");
			n->check_mov_sala(u->getID_Unidade(), comando_direcao);
	}
}

Armado::Armado(int armado) :Caracteristica("Armado"){
	setCapCombate(armado);
	cout << "Estou Armado" << endl;
}
