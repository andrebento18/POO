#pragma once
//Existem v�rias �entidades� na nave.Podem ser tripulantes ou outras coisas como por exemplo invasores.
//S�o colectivamente referidos como �unidades�.Um tripulante ser� uma unidade, mas uma unidade pode n�o ser 
//um tripulante.Num dado instante, cada unidade estar�, em princ�pio, numa determinada sala da nave.
class Sala;
class Unidade{
	Sala *ondestou;
	int ponto_vida;
	int exoesqueleto = 0; //se o exoesqueleto estiver a zero o dano � recebido normal, senao recebe dano atraves da funcao exoesqueleto
	string nome; 
	//LISTA DE CARACTERISTICAS
	bool flamejante; //0-Nao;1-Sim
	int toxico; //pontos de vida que cada unidade perde na mesma sala
	bool indeciso; //0-Nao;1-Sim 50% de prob. de ficar indeciso
	int regenerador; //quantidade de pontos de vida que regenera por turno
	bool robotico; //caso seja robotico n�o pode executar acc��es(movimento/combate/etc) em salas com curto-circuito
	int reparador; //caso n�o esteja em combate, ao terminar o turno repara x pontos
	int combatente; //caso hajam enimigos na mesma sala, provoca x pontos de dano a um enimigo na sala
public:
	Unidade(string tipo);
	~Unidade();
	int getPV()const;
	void LevaDano(int dano_recebido);
	Sala *LocalizarSala()const;
	string getNome()const;
	void setOndeEstou(Sala *a);
	void Exoesqueleto(int valor_ignorado);
};

class Unidade_MembroTripulacao : public Unidade {
	bool respira; //0-Nao;1-Sim
public:
	Unidade_MembroTripulacao(string tipo);
};

class Capitao : public Unidade {
	bool respira; //0-Nao;1-Sim
public:
	Capitao(string tipo, int exoesqueleto);
	/*Exoesqueleto(X): Previne os primeiros X pontos de dano em cada turno
	(excepto os danos identificados como �n�o pode ser evitado�).*/
	//void Exoesqueleto(int pontos_dano, int dano_ignorado);
};


class Robot : public Unidade {
	//Caracter�sticas: Exoesqueleto(2), Combatente(3), Tripula��o
public:
	Robot (string tipo, int exoesqueleto);
	/*Exoesqueleto(X): Previne os primeiros X pontos de dano em cada turno
	(excepto os danos identificados como �n�o pode ser evitado�).*/
};

//Inimigos
class Pirata : public Unidade {
	//Caracter�sticas: Respira, Inimigo(1, 2), Move(15)
	bool respira; //0-Nao;1-Sim
	int dano_ignorado_exoesqueleto = 1;
public:
	//Pirata(string tipo);
	
};