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
	for (unsigned int i = 0; i < p->countUnidades(); i++) {
		bool unidade_toxica = false;
		// Verifica se a unidade a provocar dano � t�xica
		for (unsigned int j = 0; j < p->getUnidadePosicao(i)->countCaracteristicas(); j++) {
			if (p->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca() == "Toxico") {
				unidade_toxica = true;
				break;
			}
		}
		// Se for toxica
		if (unidade_toxica != true) {
			p->getUnidadePosicao(i)->LevaDano(dano_toxico);
		}
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

Reparador::Reparador(int cap_reparar) :Caracteristica("Reparador") {
	this->cap_reparar = cap_reparar;
	cout << "Esta unidade repara " << cap_reparar << " pontos, por turno, da sala onde esta" << endl;
}

// ROBOTICO ???

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
	// FALTA ESCOLHER ALEATORIAMENTE A UNIDADE A ATACAR ??????????
	bool existe_inimigo = false;
	int	id_inimigo = 0;

	Sala *s = u->getOndeEstou();

	for (unsigned int i = 0; i < s->countUnidades(); i++) {
		for (unsigned int j = 0; j < s->getUnidadePosicao(i)->countCaracteristicas(); j++) {
			string tipo_car = s->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca();
			if (tipo_car == "Inimigo" || tipo_car == "Xenomorfo") {
				id_inimigo = s->getUnidadePosicao(i)->getID_Unidade();
				s->setOperada(false);
				s->getUnidade(id_inimigo)->LevaDano(capacidade_combate);
				break;
			}
		}
	}
}

Xenomorfo::Xenomorfo(int cap_dano):Caracteristica("Xenomorfo") {
	this->cap_dano = cap_dano;
	cout << "Esta unidade e do tipo Xenomorfo" << endl;
}

void Xenomorfo::actua_car_fim(Unidade *u, Nave *n) {
	// FALTA ESCOLHER ALEATORIAMENTE A UNIDADE A ATACAR ??????????
	bool existe_inimigo = false;
	int	id_inimigo = 0;

	Sala *s = u->getOndeEstou();

	for (unsigned int i = 0; i < s->countUnidades(); i++) {
		for (unsigned int j = 0; j < s->getUnidadePosicao(i)->countCaracteristicas(); j++) {
			string tipo_car = s->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca();
			if (tipo_car == "Tripulacao" || tipo_car == "Inimigo") {
				id_inimigo = s->getUnidadePosicao(i)->getID_Unidade();
				s->setOperada(false);
				s->getUnidade(id_inimigo)->LevaDano(cap_dano);
				break;
			}
		}
	}
}

Casulo::Casulo(int prob):Caracteristica("Casulo"), prob_casulo(prob){
	cout << "Esta unidade � capaz de aprisionar os membros da tripulacao" << endl;
}

void Casulo::actua_car_fim(Unidade * u, Nave * n){
	// ESTA A REBENTAR, TENTAR VER O QUE SE PASSA ????????????
	/*Sala *s = u->getOndeEstou();
	for (unsigned int i = 0; i < s->countUnidades(); i++) {
		for (unsigned int j = 0; j < s->getUnidadePosicao(i)->countCaracteristicas(); j++) {
			string tipo_car = s->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca();
			if (tipo_car == "Tripulacao") {
				if (random(1, 100) <= prob_casulo) {
					new CasulodeGeigermorfo("Casulo de Geigermorfo", s->getUnidadePosicao(i));
					break;
				}
			}
		}
	}*/
}


Mutantis_Mutandis::Mutantis_Mutandis(int prob) :Caracteristica("Mutantis_Mutandis") {
	this->prob = prob;
	cout << "Esta unidade � capaz de alterar a sala onde se encontra com " << prob << " % probabilidade" << endl;
}

void Mutantis_Mutandis::actua_car_inicio(Unidade * u, Nave * n){
	if (random(1, 100) <= prob) {
		if (u->getOndeEstou() == n->getSala(2) || u->getOndeEstou() == n->getSala(3) || u->getOndeEstou() == n->getSala(4) || u->getOndeEstou() == n->getSala(10) || u->getOndeEstou() == n->getSala(11) || u->getOndeEstou() == n->getSala(12)) {
			int escolha_sala = 1; // random(1, 9);
			switch (escolha_sala) {
				case 1: {
					// Propulsor Adicional
					cout << "Construo sala 1";
					Sala *s = new SalaPropulsor("Propulsor Adicional");
					//s = u->getOndeEstou();
					cout << s->toString();
					system("pause");
					break; 
				}
						// COMO CONTRUIR SALAS IGUAIS MAS COM TIPO DIFERENTE ?????????
				/*case 2:
					cout << "Construo sala 2";
					system("pause");
					break;
				case 3:
					cout << "Construo sala 3";
					system("pause");
					break;
				case 4:
					cout << "Construo sala 4";
					system("pause");
					break;
				case 5:
					cout << "Construo sala 5";
					system("pause");
					break;
				case 6:
					cout << "Construo sala 6";
					system("pause");
					break;
				case 7:
					cout << "Construo sala 7";
					system("pause");
					break;
				case 8:
					cout << "Construo sala 8";
					system("pause");
					break;
				case 9:
					cout << "Construo sala 9";
					system("pause");
					break;*/
			}
		}
	}
}

Hipnotizador::Hipnotizador(int prob_hip):Caracteristica("Hipnotizador"){
	this->prob_hip = prob_hip;
	cout << "Esta unidade e capaz de hipnotizar outra" << endl;
}

void Hipnotizador::actua_car_inicio(Unidade *u, Nave *n) {
	// Verificar e seleccionar unidade Tripulacao
	Sala *s = u->getOndeEstou();
	for (unsigned int i = 0; i < s->countUnidades(); i++) {
		for (unsigned int j = 0; j < s->getUnidadePosicao(i)->countCaracteristicas(); j++) {
			string tipo_car = s->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca();
			if (tipo_car == "Tripulacao") {
				s->getUnidadePosicao(i)->setCaracteristica(new Indeciso());
				break;
			}
		}
	}
}


Operador::Operador(void) :Caracteristica("Operador") {
	cout << "Esta unidade e capaz de operar salas" << endl;
}

void Operador::actua_car_inicio(Unidade *u, Nave *n) {
	// FALATA VERIFICAR SE EST� EM COMBATE ???????? (NAO VAI L� S� COM O FACTO DE A SALA NAO ESTAR OPERADA)
	if (u->getOndeEstou()->getIntegridade() == 100)
		u->getOndeEstou()->setOperada(true);
}

Tripulacao::Tripulacao(void):Caracteristica("Tripulacao") {
	cout << "Faco parte da tripulacao da nave" << endl;
}

Inimigo::Inimigo(int x, int y):dano_unidade(x), dano_sala(y), Caracteristica("Inimigo") {
	cout << "Esta unidade provoca " << dano_unidade << " pontos de dano a unidades inimigas ou " << dano_sala << " pontos de dano a salas" << endl;
}

void Inimigo::actua_car_inicio(Unidade *u, Nave *n) {
	bool existe_inimigo = false;
	int id_inimigo = 0;

	Sala *s = u->getOndeEstou();

	// Verificar se existe inimigo
	for (unsigned int i = 0; i < s->countUnidades(); i++) {
		for (unsigned int j = 0; j < s->getUnidadePosicao(i)->countCaracteristicas(); j++) {
			string tipo_car = s->getUnidadePosicao(i)->getCaracteristicaPosicao(j)->getTipoCaracterisca();
			if (tipo_car == "Xenomorfo" || tipo_car == "Tripulacao") {
				existe_inimigo = true;
				id_inimigo = s->getUnidadePosicao(i)->getID_Unidade();
				break;
			}
		}
	}

	if(existe_inimigo == true){
		s->getUnidade(id_inimigo)->LevaDano(dano_unidade);
	}
	else {
		u->getOndeEstou()->reduzIntegridade(dano_sala);
	}
}

Move::Move(int pmovimento):Caracteristica("Move"), prob_movimento(pmovimento) {
	cout << "Esta unidade pode mover-se para outra sala com prob. " << prob_movimento << " %" << endl;
}

void Move::actua_car_inicio(Unidade *u, Nave *n) {
	if (random(1, 100) < prob_movimento) {
		// Obter id_sala onde se encontra a unidade
		int id_sala = u->getOndeEstou()->getID();
		// Sortear o movimento "cima", "baixo", "esquerda", "direita"
		string comando_direcao;
		bool moveu = false;
		do {
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
			// Verificar a possibilidade de movimento e efectu�-lo caso seja poss�vel
			if (n->check_mov_sala(u->getID_Unidade(), comando_direcao) == true)
				moveu = true;
			else
				continue;
		} while (moveu == false);
	}
}

Armado::Armado(int armado) :Caracteristica("Armado"){
	setCapCombate(armado);
	cout << "Estou Armado" << endl;
}