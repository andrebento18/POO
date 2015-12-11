#pragma once
//Existem várias “entidades” na nave.Podem ser tripulantes ou outras coisas como por exemplo invasores.
//São colectivamente referidos como “unidades”.Um tripulante será uma unidade, mas uma unidade pode não ser 
//um tripulante.Num dado instante, cada unidade estará, em princípio, numa determinada sala da nave.
class Sala;
class Unidade{
	Sala *ondestou = NULL;
	int pv;
	string nome; 
	//LISTA DE CARACTERISTICAS
	bool respira; //0-Nao;1-Sim
	bool flamejante; //0-Nao;1-Sim
	int toxico; //pontos de vida que cada unidade perde na mesma sala
	bool indeciso; //0-Nao;1-Sim 50% de prob. de ficar indeciso
	int regenerador; //quantidade de pontos de vida que regenera por turno
	bool robotico; //caso seja robotico não pode executar accções(movimento/combate/etc) em salas com curto-circuito
	int reparador; //caso não esteja em combate, ao terminar o turno repara x pontos
	int combatente; //caso hajam enimigos na mesma sala, provoca x pontos de dano a um enimigo na sala
public:
	Unidade();
	~Unidade();
	int getPV()const;
	Sala *LocalizarSala()const;
	string getNome()const;
	void setOndeEstou(Sala *a);
};