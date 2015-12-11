#include <iostream>
#include <string>

using namespace std;
#include "unidade.h"

Unidade::Unidade() {
	// COMO CRIAR VARIOS TIPOS DE UNIDADES???
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
