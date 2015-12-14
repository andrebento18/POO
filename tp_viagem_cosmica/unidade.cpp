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
	return pv;
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

Unidade_MembroTripulacao::Unidade_MembroTripulacao(string tipo):Unidade(tipo){
	respira = true;
}
