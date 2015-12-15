#pragma once
//Existem v�rias �entidades� na nave.Podem ser tripulantes ou outras coisas como por exemplo invasores.
//S�o colectivamente referidos como �unidades�.Um tripulante ser� uma unidade, mas uma unidade pode n�o ser 
//um tripulante.Num dado instante, cada unidade estar�, em princ�pio, numa determinada sala da nave.
class Sala;
class Unidade{
	Sala *ondestou;
	int pv;
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
	Sala *LocalizarSala()const;
	string getNome()const;
	void setOndeEstou(Sala *a);
};

class Unidade_MembroTripulacao : public Unidade {
	bool respira; //0-Nao;1-Sim
public:
	Unidade_MembroTripulacao(string tipo);
};