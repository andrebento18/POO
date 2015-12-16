#include <iostream>
#include <string>
using namespace std;

#include "unidade.h"

Unidade::Unidade(string tipo) {
	nome = tipo;
	ondestou = NULL;
}

Unidade::~Unidade() {
	cout << "Unidade destruida" << endl;
}

int Unidade::getPV()const {
	return ponto_vida;
}

void Unidade::LevaDano(int dano_recebido)
{
	ponto_vida = ponto_vida - dano_recebido;
}

Sala * Unidade::LocalizarSala() const
{
	return ondestou;
}

string Unidade::getNome() const
{
	return nome;
}

void Unidade::setOndeEstou(Sala * a)
{
	ondestou = a;
}



void Unidade::Exoesqueleto(int valor_ignorado)
{
	exoesqueleto = valor_ignorado;
}

Unidade_MembroTripulacao::Unidade_MembroTripulacao(string tipo):Unidade(tipo){
	respira = true;
}

Capitao::Capitao(string tipo, int exoesqueleto) : Unidade(tipo) {
	respira = true;
	Exoesqueleto(exoesqueleto); //mete o exosqueleto com o valor a ser ignorado
	
}

Robot::Robot(string tipo, int exoesqueleto) : Unidade(tipo) {
	Exoesqueleto(exoesqueleto); //mete o exosqueleto com o valor a ser ignorado

}



