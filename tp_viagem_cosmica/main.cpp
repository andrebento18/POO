#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <MMSystem.h>
using namespace std;
#include "util.h"
#include "ConsolaG++.h"
#include "nave.h"

bool verifica_vitoria(Nave *nave, double nvl) {
	Consola c;
	if (nave->getDistancia() > 4000 + 1000  * nvl) {
		// vitória
		PlaySound(NULL, NULL, 0);
		PlaySound(TEXT("./SOUND/Victory.wav"), NULL, SND_LOOP | SND_ASYNC);
		c.clrscr();
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----VITORIA-----";
			}
			cout << endl;
		}
		cout << "Parabens, prime uma tecla para voltar ao menu inicial" << endl;
		c.getch();
		return 1;
	}else
		// sem vitória
		return 0;
}

bool verifica_derrota(Nave *nave) {
	Consola c;
	if (nave->verifica_saudeNave() == 0) {
		// derrota devido a destruicao de uma sala 
		c.clrscr();
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----GAME-OVER-----";
			}
			cout << endl;
		}
		cout << "Uma sala da tua nave foi destruida, prime uma tecla para voltar ao menu inicial e tentar novamente" << endl;
		c.getch();
		return 1;
	}
	else if (nave->countTripulacao() == 0) {
		// derrota devido a perda da tripulacao
		c.clrscr();
		for (int i = 0; i <= 30; i++) {
			for (int j = 0; j <= 3; j++) {
				cout << "-----GAME-OVER-----";
			}
			cout << endl;
		}
		cout << "Ficaste sem tripulacao, prime uma tecla para voltar ao menu inicial e tentar novamente" << endl;
		c.getch();
		return 1;
	}
	else
		// sem derrota
		return 0;
}

void interface_nave(Nave *nave, int turnos, int nvl) {
	Consola c;
	c.clrscr();

	cout << "Turno(s): " << turnos << "\t\t\t\tTripulacao: " << nave->countTripulacao() << " unidade(s)" << "\t\t\t\t\tInterface grafica da nave:" << endl;
	c.gotoxy(80, 3);
	cout << "Distancia total percorrida: " << nave->getDistancia() << " milhas\t\t\tFaltam: " << (4000 + 1000 * nvl) - nave->getDistancia() << " milhas para completar a missao";

	// Desenha centro da nave
	for (int i = 0; i <= 180; i++) {
		for (int j = 0; j <= 25; j++) {
			c.gotoxy(i, j);
			// 1ª linha horizontal
			if ((i == 80 || i == 100 || i == 120 || i == 140) && j == 5)
				cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
			// 2ª linha horizontal
			if ((i == 80 || i == 100 || i == 120 || i == 140) && j == 11)
				cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';
			// 3ª linha horizontal
			if ((i == 100 || i == 120 || i == 140 || i == 160) && j == 12)
				cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
			// 4ª linha horizontal
			if ((i == 100 || i == 120 || i == 140 || i == 160) && j == 18)
				cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';
			// 5 ªlinha horizontal
			if ((i == 80 || i == 100 || i == 120 || i == 140) && j == 19)
				cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << '\n';
			// 6ª linha horizontal
			if ((i == 80 || i == 100 || i == 120 || i == 140) && j == 25)
				cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << '\n';
			// linhas verticais propulsores
			if((i == 80 || i == 99) && ((j > 5 && j < 11) || (j > 19 && j < 25)))
				cout << (char)179;
			// linhas verticais centro ESQ
			if ((i == 100 || i == 120 || i == 140) && ((j > 5 && j < 11) || (j > 12 && j < 18) || (j > 19 && j < 25)))
				cout << (char)179;
			// linhas verticais centro DIR
			if ((i == 119 || i == 139 || i == 159) && ((j > 5 && j < 11) || (j > 12 && j < 18) || (j > 19 && j < 25)))
				cout << (char)179;
			// linhas verticais ponte
			if ((i == 160 || i == 179) && (j > 12 && j < 18))
				cout << (char)179;
		}
	}

	// Stats Salas
	// Sala 1
	c.gotoxy(81, 6); cout << "SALA 1";
	c.gotoxy(81, 7); cout << "INTG: " << nave->getSala(1)->getIntegridade();
	c.gotoxy(81, 8); cout << "OXIG: " << nave->getSala(1)->getOxigenio();
	c.gotoxy(81, 9); cout << "OPER: " << nave->getSala(1)->getOperada() << "    FOGO: " << nave->getSala(1)->getFogo();
	c.gotoxy(81, 10); cout << "BREC: " << nave->getSala(1)->getBrecha() << "    CUCR: " << nave->getSala(1)->getCurtoCircuito();

	// Sala 2
	c.gotoxy(101, 6); cout << "SALA 2";
	c.gotoxy(101, 7); cout << "INTG: " << nave->getSala(2)->getIntegridade();
	c.gotoxy(101, 8); cout << "OXIG: " << nave->getSala(2)->getOxigenio();
	c.gotoxy(101, 9); cout << "OPER: " << nave->getSala(2)->getOperada() << "    FOGO: " << nave->getSala(2)->getFogo();
	c.gotoxy(101, 10); cout << "BREC: " << nave->getSala(2)->getBrecha() << "    CUCR: " << nave->getSala(2)->getCurtoCircuito();

	// Sala 3
	c.gotoxy(121, 6); cout << "SALA 3";
	c.gotoxy(121, 7); cout << "INTG: " << nave->getSala(3)->getIntegridade();
	c.gotoxy(121, 8); cout << "OXIG: " << nave->getSala(3)->getOxigenio();
	c.gotoxy(121, 9); cout << "OPER: " << nave->getSala(3)->getOperada() << "    FOGO: " << nave->getSala(3)->getFogo();
	c.gotoxy(121, 10); cout << "BREC: " << nave->getSala(3)->getBrecha() << "    CUCR: " << nave->getSala(3)->getCurtoCircuito();

	// Sala 4
	c.gotoxy(141, 6); cout << "SALA 4";
	c.gotoxy(141, 7); cout << "INTG: " << nave->getSala(4)->getIntegridade();
	c.gotoxy(141, 8); cout << "OXIG: " << nave->getSala(4)->getOxigenio();
	c.gotoxy(141, 9); cout << "OPER: " << nave->getSala(4)->getOperada() << "    FOGO: " << nave->getSala(4)->getFogo();
	c.gotoxy(141, 10); cout << "BREC: " << nave->getSala(4)->getBrecha() << "    CUCR: " << nave->getSala(4)->getCurtoCircuito();

	// Sala 5
	c.gotoxy(101, 13); cout << "SALA 5";
	c.gotoxy(101, 14); cout << "INTG: " << nave->getSala(5)->getIntegridade();
	c.gotoxy(101, 15); cout << "OXIG: " << nave->getSala(5)->getOxigenio();
	c.gotoxy(101, 16); cout << "OPER: " << nave->getSala(5)->getOperada() << "    FOGO: " << nave->getSala(5)->getFogo();
	c.gotoxy(101, 17); cout << "BREC: " << nave->getSala(5)->getBrecha() << "    CUCR: " << nave->getSala(5)->getCurtoCircuito();

	// Sala 6
	c.gotoxy(121, 13); cout << "SALA 6";
	c.gotoxy(121, 14); cout << "INTG: " << nave->getSala(6)->getIntegridade();
	c.gotoxy(121, 15); cout << "OXIG: " << nave->getSala(6)->getOxigenio();
	c.gotoxy(121, 16); cout << "OPER: " << nave->getSala(6)->getOperada() << "    FOGO: " << nave->getSala(6)->getFogo();
	c.gotoxy(121, 17); cout << "BREC: " << nave->getSala(6)->getBrecha() << "    CUCR: " << nave->getSala(6)->getCurtoCircuito();

	// Sala 7
	c.gotoxy(141, 13); cout << "SALA 7";
	c.gotoxy(141, 14); cout << "INTG: " << nave->getSala(7)->getIntegridade();
	c.gotoxy(141, 15); cout << "OXIG: " << nave->getSala(7)->getOxigenio();
	c.gotoxy(141, 16); cout << "OPER: " << nave->getSala(7)->getOperada() << "    FOGO: " << nave->getSala(7)->getFogo();
	c.gotoxy(141, 17); cout << "BREC: " << nave->getSala(7)->getBrecha() << "    CUCR: " << nave->getSala(7)->getCurtoCircuito();

	// Sala 8
	c.gotoxy(161, 13); cout << "SALA 8";
	c.gotoxy(161, 14); cout << "INTG: " << nave->getSala(8)->getIntegridade();
	c.gotoxy(161, 15); cout << "OXIG: " << nave->getSala(8)->getOxigenio();
	c.gotoxy(161, 16); cout << "OPER: " << nave->getSala(8)->getOperada() << "    FOGO: " << nave->getSala(8)->getFogo();
	c.gotoxy(161, 17); cout << "BREC: " << nave->getSala(8)->getBrecha() << "    CUCR: " << nave->getSala(8)->getCurtoCircuito();

	// Sala 9
	c.gotoxy(81, 20); cout << "SALA 9";
	c.gotoxy(81, 21); cout << "INTG: " << nave->getSala(9)->getIntegridade();
	c.gotoxy(81, 22); cout << "OXIG: " << nave->getSala(9)->getOxigenio();
	c.gotoxy(81, 23); cout << "OPER: " << nave->getSala(9)->getOperada() << "    FOGO: " << nave->getSala(9)->getFogo();
	c.gotoxy(81, 24); cout << "BREC: " << nave->getSala(9)->getBrecha() << "    CUCR: " << nave->getSala(9)->getCurtoCircuito();

	// Sala 10
	c.gotoxy(101, 20); cout << "SALA 10";
	c.gotoxy(101, 21); cout << "INTG: " << nave->getSala(10)->getIntegridade();
	c.gotoxy(101, 22); cout << "OXIG: " << nave->getSala(10)->getOxigenio();
	c.gotoxy(101, 23); cout << "OPER: " << nave->getSala(10)->getOperada() << "    FOGO: " << nave->getSala(10)->getFogo();
	c.gotoxy(101, 24); cout << "BREC: " << nave->getSala(10)->getBrecha() << "    CUCR: " << nave->getSala(10)->getCurtoCircuito();
	
	// Sala 11
	c.gotoxy(121, 20); cout << "SALA 11";
	c.gotoxy(121, 21); cout << "INTG: " << nave->getSala(11)->getIntegridade();
	c.gotoxy(121, 22); cout << "OXIG: " << nave->getSala(11)->getOxigenio();
	c.gotoxy(121, 23); cout << "OPER: " << nave->getSala(11)->getOperada() << "    FOGO: " << nave->getSala(11)->getFogo();
	c.gotoxy(121, 24); cout << "BREC: " << nave->getSala(11)->getBrecha() << "    CUCR: " << nave->getSala(11)->getCurtoCircuito();

	// Sala 12
	c.gotoxy(141, 20); cout << "SALA 12";
	c.gotoxy(141, 21); cout << "INTG: " << nave->getSala(12)->getIntegridade();
	c.gotoxy(141, 22); cout << "OXIG: " << nave->getSala(12)->getOxigenio();
	c.gotoxy(141, 23); cout << "OPER: " << nave->getSala(12)->getOperada() << "    FOGO: " << nave->getSala(12)->getFogo();
	c.gotoxy(141, 24); cout << "BREC: " << nave->getSala(12)->getBrecha() << "    CUCR: " << nave->getSala(12)->getCurtoCircuito();
	
	c.gotoxy(1, 1);
	cout << nave->getSalas() << endl;
}

void viagem(Nave *nave, double nvl) {
	Consola c;
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("./SOUND/Space_Cruise.wav"), NULL, SND_LOOP | SND_ASYNC);
	c.clrscr();
	/////////////// VIAGEM ///////////////
	int turnos = 0;
	int event_ocurr = 0;

	do {
		c.clrscr();
		// 1. INICIO DO TURNO
		turnos++;
		
		nave->inicio_turno();

		// 2. FASE DE ORDENS
		string cmd;
		do {
			interface_nave(nave, turnos, nvl);
			
			c.gotoxy(80, 40);
			cout << "De as ordens meu comandante...";
			c.gotoxy(80, 41);
			cout << "CMD> "; cin >> cmd;
			if (cmd == "mover") {
				int id_unidade;
				string dir_mov;
				c.gotoxy(80, 42);
				cout << "Que unidade deseja mover? "; cin >> id_unidade;
				c.gotoxy(80, 43);
				cout << "Para que sala? (Segundo uma orientação) "; cin >> dir_mov; cout << endl;

				nave->check_mov_sala(id_unidade, dir_mov);
			}
			else if (cmd == "fim")
			{
				c.gotoxy(80, 42);
				cout << "Desististe do jogo, prime uma tecla para voltar ao menu inicial";
				c.getch();
				return;
			}
			else if(cmd != "avancar" && cmd != "fim") {
				c.gotoxy(80, 42);
				cout << "Nao conheco esse comando meu comandante..." << endl;
				c.getch();
			}
		} while (cmd != "avancar");

		c.clrscr();
		c.gotoxy(3, 1);
		cout << "Relatorio do final do turno" << endl;

		// 3. FINAL DO TURNO

		nave->fim_turno();

		// 4. EVENTOS
		if (event_ocurr == 0) {
			nave->evento();
			event_ocurr = random(5, 10);
		}
		else {
			event_ocurr--;
			cout << "Estamos com sorte, nao tivemos precalcos a avancar comandante!" << endl;
		}

		cout << "Prime uma tecla pra avancar o turno..." << endl;
		c.getch();
	} while (verifica_vitoria(nave, nvl) == 0 && verifica_derrota(nave) == 0);
}

void ajuda() {
	Consola c;
	c.clrscr();
	c.gotoxy(20, 5);
	cout << "MENU-AJUDA" << endl;
	c.gotoxy(1, 8);
	cout << "\tVais assumir o comando de uma nave espacial que efectua uma perigosa viagem intergalatica.\n\tA nave esta organizada em diferentes salas, cada uma com diversos equipamentos e objectivos para a producao dos recursos necessarios a viagem.\n\tAs salas tem diferentes funcoes (consoante o tipo de sala) e o seu comportamento pode depender de se encontrarem nela tripulantes (ou nao).\n\n\tAs salas que podes adicionar sao:\n\t-> Propulsor Adicional\n\t-> Beliche\n\t-> Raio Laser\n\t-> Auto-reparador\n\t-> Sistema de Seguranca interno\n\t-> Enfermaria\n\t-> Sala de armas\n\t-> Alojamentos do Capitao\n\t-> Oficina Robotica\n\n\tA tripulacao e constituida por varios tipos de tripulantes, cada um com determinadas caracteristicas e que desempenham tarefas essenciais como pilotar a nave, reparar danos, operar\n   as armas, lutar contra invasores e as actividades.\n\n\tTripulantes disponiveis:\n\t-> Membro da Tripulacao\n\t-> Capitao\n\t-> Robot\n\n\tDurante a viagem podem ocorrer diversas situacoes (ataque e invasao de piratas, invasao de alienigenas, chuva de meteoritos, etc.).\n\n\tO jogo consiste em gerir a nave (salas, tripulacao, recursos) e decorre numa grelha, que representa a nave. Esta inclui diferentes salas e equipamentos.\n\tA tripulacao e limitada e deve ser bem gerida para conseguir operar as salas e equipamentos.\n\tO jogo decorre por turnos: em cada turno tens a oportunidade de decidir e dizer o que os teus tripulantes da nave devem fazer.\n\n\tAs indicacoes são dadas segundo comandos escritos.\n\n\t<avancar>\n\t<mover>\n\t<fim>" << endl;
	c.getch();
}

void menu_inicial() {
	Consola c;
	c.clrscr();
	c.setTextColor(c.VERDE_CLARO);
	c.setBackgroundColor(c.PRETO);

	string cmd;
	do {
		c.clrscr();
		c.gotoxy(21, 18);
		cout << "VIAGEM-COSMICA" << endl;
		c.gotoxy(15, 21);
		cout << "Escreva o que deseja fazer: \n\t\t\t<jogar> \n\t\t\t<ajuda> \n\t\t\t<fim>\n" << endl;
		c.gotoxy(15, 25);
		cout << "CMD> "; cin >> cmd;
		if (cmd == "jogar") {
			double nvl;
			do {
				c.clrscr();
				c.gotoxy(20, 20);
				cout << "Insira a dificuldade da missao: ";
				cin >> nvl;
			} while (nvl <= 0);

			c.clrscr();

			Nave nave;

			c.gotoxy(20, 20);
			cout << "Prima uma tecla para comecar a viagem..." << endl;
			c.getch();

			viagem(&nave, nvl);
		}
		else if (cmd == "ajuda") {
			ajuda();
		}
	} while (cmd != "fim");
}

int main(void) {
	PlaySound(NULL, NULL, 0);
	PlaySound(TEXT("./SOUND/Cosmos.wav"), NULL, SND_LOOP | SND_ASYNC);
	system("mode 800");

	menu_inicial();

	return 0;
}


