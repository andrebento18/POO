#pragma once
//Existem v�rias �entidades� na nave.Podem ser tripulantes ou outras coisas como por exemplo invasores.
//S�o colectivamente referidos como �unidades�.Um tripulante ser� uma unidade, mas uma unidade pode n�o ser 
//um tripulante.Num dado instante, cada unidade estar�, em princ�pio, numa determinada sala da nave.
class Sala;
class Unidade{
	Sala *ondestou;
	int ponto_vida;
	string nome; 
	//LISTA DE CARACTERISTICAS
	bool respira; //0-Nao;1-Sim
	bool flamejante; //0-Nao;1-Sim
	int toxico; //pontos de vida que cada unidade perde na mesma sala
	bool indeciso; //0-Nao;1-Sim 50% de prob. de ficar indeciso
	bool misterioso; //
	int exoesqueleto; //se o exoesqueleto estiver a zero o dano � recebido normal, senao recebe dano atraves da funcao exoesqueleto
	bool robotico; //caso seja robotico n�o pode executar acc��es(movimento/combate/etc) em salas com curto-circuito
	int reparador;
	int combatente; //caso hajam enimigos na mesma sala, provoca x pontos de dano a um enimigo na sala
	int xenomorfo; //
	int casulo;
	int mutatis_mutandis;//
	int hipnotizador;
	bool operador;
	bool tripulacao;
	int regenerador; //quantidade de pontos de vida que regenera por turno
	//bool inimigo(x,y)
	int combatente;
	int move;
	int armado;
	
	
public:
	Unidade(string tipo, int pv);
	virtual ~Unidade();
	int getPV()const;
	void LevaDano(int dano_recebido);
	Sala *LocalizarSala()const;
	string getNome()const;
	void setOndeEstou(Sala *a);
};

class Unidade_MembroTripulacao : public Unidade {
public:
	Unidade_MembroTripulacao(string tipo);
};

class Capitao : public Unidade {
	
public:
	Capitao(string tipo);
	/*Exoesqueleto(X): Previne os primeiros X pontos de dano em cada turno
	(excepto os danos identificados como �n�o pode ser evitado�).*/
	//void Exoesqueleto(int pontos_dano, int dano_ignorado);
};


class Robot : public Unidade {
	//Caracter�sticas: Exoesqueleto(2), Combatente(3), Tripula��o
	
public:
	Robot (string tipo);
	/*Exoesqueleto(X): Previne os primeiros X pontos de dano em cada turno
	(excepto os danos identificados como �n�o pode ser evitado�).*/
};

//Inimigos
class Pirata : public Unidade {
	//Caracter�sticas: Respira, Inimigo(1, 2), Move(15)
	bool respira; //0-Nao;1-Sim
public:
	//Pirata(string tipo);
	
};