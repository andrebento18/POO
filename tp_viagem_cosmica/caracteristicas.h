#pragma once
class Unidade;
class Caracteristica {
public:
	virtual void Actua(Unidade *u) {
	};
};

////LISTA DE CARACTERISTICAS
//bool flamejante; //0-Nao;1-Sim
//int toxico; //pontos de vida que cada unidade perde na mesma sala
//bool indeciso; //0-Nao;1-Sim 50% de prob. de ficar indeciso
//bool misterioso; //
//int exoesqueleto; //se o exoesqueleto estiver a zero o dano � recebido normal, senao recebe dano atraves da funcao exoesqueleto
//bool robotico; //caso seja robotico n�o pode executar acc��es(movimento/combate/etc) em salas com curto-circuito
//int reparador;
//int combatente; //caso hajam enimigos na mesma sala, provoca x pontos de dano a um enimigo na sala
//int xenomorfo; //
//int casulo;
//int mutatis_mutandis;//
//int hipnotizador;
//bool operador;
//bool tripulacao;
//int regenerador; //quantidade de pontos de vida que regenera por turno
//				 //bool inimigo(x,y)
//int move;
//int armado;

class Respira : public Caracteristica {
	int respira;
public:
	Respira() {
		cout << "car respira adicionada"<< endl;
		respira = 2;
	}
	void Respirar() {
	};
};