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
	if (u->getOndeEstou()->getOxigenio() == 0)
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

void Toxico::actua_car_inicio(Unidade * u, Nave * n) {
	Sala *p = u->getOndeEstou();
	// Unidades
	for (unsigned int i = 0; i < p->countUnidades(); i++)
		p->getUnidadePosicao(i)->LevaDano(dano_toxico);
	// Piratas
	for (unsigned int i = 0; i < p->countPiratas(); i++)
		p->getPirataPosicao(i)->LevaDano(dano_toxico);
	// Xenomorfos
	for (unsigned int i = 0; i < p->countXenomorfo(); i++) {
		// Verifica se a unidade a provocar dano é tóxica
		if (p->getUnidadePosicao(i)->getCaracteristicaTipo("Toxico") != NULL)
			break;
		else
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
		u->mover_unidade(u->getOndeEstou(), n->getSala(sala_escolhida));
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

Exoesqueleto::Exoesqueleto(int cap_exoesqueleto):Caracteristica("Exoesqueleto") {
	bool existe_inimigos = false;
	this->cap_exoesqueleto = cap_exoesqueleto;
	cout << "Esta unidade esta protegida por um exoesqueleto " << this->cap_exoesqueleto << " pontos de capacidade" << endl;
}

void Exoesqueleto::actua_car_inicio(Unidade * u, Nave * n){
	if (u->getCaracteristicaTipo("Tripulacao") != NULL && (u->getOndeEstou()->countPiratas() > 0 || u->getOndeEstou()->countXenomorfo() > 0))
		existe_inimigos = true;
	else if (u->getCaracteristicaTipo("Xenomorfo") != NULL && (u->getOndeEstou()->countPiratas() > 0 || u->getOndeEstou()->countUnidades() > 0))
		existe_inimigos = true;
	if(existe_inimigos == true)
		u->aumentaPV(cap_exoesqueleto);
}

void Exoesqueleto::actua_car_fim(Unidade *u, Nave *n) {
	if (existe_inimigos == true) {
		u->LevaDano(cap_exoesqueleto);
		existe_inimigos = false;
	}
}

// FALTA IMPLEMENTAR O FACTO DE NÃO SE PODER MOVER QUANDO ESTA NUMA SALA COM CURTO-CIRCUITO ???????????
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
		if (u->getCaracteristicaTipo("Tripulacao") != NULL && (u->getOndeEstou()->countPiratas() != 0 || u->getOndeEstou()->countXenomorfo() != 0))
			existe_inimigos = true;
		else if (u->getCaracteristicaTipo("Xenomorfo") != NULL && (u->getOndeEstou()->countPiratas() != 0 || u->getOndeEstou()->countUnidades() != 0))
			existe_inimigos = true;

		if (existe_inimigos == false)
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

	Sala *s = u->getOndeEstou();

	// Atacar Piratas
	if (s->countPiratas() > 0) {
		id_inimigo = random(0, s->countPiratas() - 1);
		s->getPirataPosicao(id_inimigo)->LevaDano(capacidade_combate);
		return;
	}
	// Atacar Xenomorfos
	else if (s->countXenomorfo() > 0) {
		id_inimigo = random(0, s->countXenomorfo() - 1);
		s->getXenomorfoPosicao(id_inimigo)->LevaDano(capacidade_combate);
		return;
	}
}

Xenomorfo::Xenomorfo(int cap_dano):Caracteristica("Xenomorfo") {
	this->cap_dano = cap_dano;
	cout << "Esta unidade e do tipo Xenomorfo" << endl;
}

void Xenomorfo::actua_car_fim(Unidade *u, Nave *n) {
	int	id_inimigo = 0;

	Sala *s = u->getOndeEstou();

	// Atacar Unidades
	if (s->countUnidades() > 0) {
		id_inimigo = random(0, s->countUnidades() - 1);
		s->getUnidadePosicao(id_inimigo)->LevaDano(cap_dano);
		return;
	}
	// Atacar Piratas
	else if (s->countPiratas() > 0) {
		id_inimigo = random(0, s->countPiratas() - 1);
		s->getPirataPosicao(id_inimigo)->LevaDano(cap_dano);
		return;
	}
}

Casulo::Casulo(int prob):Caracteristica("Casulo"), prob_casulo(prob){
	cout << "Esta unidade é capaz de aprisionar os membros da tripulacao" << endl;
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
	} while (comeu != 1);
}


Mutantis_Mutandis::Mutantis_Mutandis(int prob) :Caracteristica("Mutantis_Mutandis") {
	this->prob = prob;
	cout << "Esta unidade é capaz de alterar a sala onde se encontra com " << prob << " % probabilidade" << endl;
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

void Operador::actua_car_inicio(Unidade *u, Nave *n) {
	bool existe_inimigos = false;
	if (u->getCaracteristicaTipo("Tripulacao") != NULL && (u->getOndeEstou()->countPiratas() != 0 || u->getOndeEstou()->countXenomorfo() != 0))
		existe_inimigos = true;
	else if (u->getCaracteristicaTipo("Xenomorfo") != NULL && (u->getOndeEstou()->countPiratas() != 0 || u->getOndeEstou()->countUnidades() != 0))
		existe_inimigos = true;
	
	if (u->getOndeEstou()->getIntegridade() == 100 && existe_inimigos == false)
		u->getOndeEstou()->setOperada(true);
}

Tripulacao::Tripulacao(void):Caracteristica("Tripulacao") {
	cout << "Faco parte da tripulacao da nave" << endl;
}

Inimigo::Inimigo(int x, int y):dano_unidade(x), dano_sala(y), Caracteristica("Inimigo") {
	cout << "Esta unidade provoca " << dano_unidade << " pontos de dano a unidades inimigas ou " << dano_sala << " pontos de dano a salas" << endl;
}

void Inimigo::actua_car_inicio(Unidade *u, Nave *n) {
	int	id_inimigo = 0;

	Sala *s = u->getOndeEstou();

	// Atacar Tripulacao
	if (s->countUnidades() > 0) {
		id_inimigo = random(0, s->countUnidades() - 1);
		s->getUnidadePosicao(id_inimigo)->LevaDano(dano_unidade);
		return;
	}
	// Atacar Xenomorfos
	else if (s->countXenomorfo() > 0) {
		id_inimigo = random(0, s->countXenomorfo() - 1);
		s->getXenomorfoPosicao(id_inimigo - 1)->LevaDano(dano_unidade);
		return;
	}
	// Não existe enimigo
	else
		u->getOndeEstou()->reduzIntegridade(dano_sala);
}

Move::Move(int pmovimento):Caracteristica("Move"), prob_movimento(pmovimento) {
	cout << "Esta unidade pode mover-se para outra sala com prob. " << prob_movimento << " %" << endl;
}

void Move::actua_car_inicio(Unidade *u, Nave *n) {
	if (random(1, 100) < prob_movimento) {
		// Sortear o movimento "cima", "baixo", "esquerda", "direita"
		//do {
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
			cout << "COMD>" << comando_direcao << endl;
			system("pause");

			/*if (*/
			n->check_mov_sala(u->getID_Unidade(), comando_direcao); /* == true) {
				cout << "Unidade " << u->getID_Unidade() + 1 << " movida para " << comando_direcao << endl;
				system("pause");
				*/
			/*	return;
			}
		} while (1);
		*/
	}
}

Armado::Armado(int armado) :Caracteristica("Armado"){
	setCapCombate(armado);
	cout << "Estou Armado" << endl;
}
