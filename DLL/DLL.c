
#include <windows.h>
#include "DLL.h"

//Defini��o da vari�vel global
/* ----------------------------------------------------- */
/*  CONSTANTES											 */
/* ----------------------------------------------------- */
#define SIZE_USERNAME		30									// Max chars do utilizador
#define TAM_BUFFER			20									// Tamanho de Buffer a utilizar no CLiente
#define MAXCLIENTES			4									// Maximo de Clientes 
#define MAXJOGADORES		4									// Max jogadores permitido
#define NUMTIPOOBJECTOS		10									// Tipo de objectos existentes
#define SIZEMENSAGEM		sizeof(Msg)							// Tamanho da estrutura Msg
#define SIZE_MEM_GERAL		sizeof(MemGeral)					// Tamanho da Memoria Partilhada Geral
#define NOME_MEM_GERAL		TEXT("SharedMemGeral")				// Nome da Memoria Partilhada Geral
#define SEM_MEM_GERAL		TEXT("SemaforoSharedMemGeral")		// Nome do Semaforo da Memoria Partilha Geral
#define EVNT_MEM_GERAL		TEXT("EventoSharedMemGeral")		// Nome do Evento da Memoria Partilha Geral
#define SEM_MEM_DINAMICA	TEXT("SemaforoSharedMemDinamica")	// Nome do Semaforo da Memoria Partilha Dinamica
#define EVNT_MEM_DINAMICA	TEXT("EventoSharedMemDinamica")		// Nome do Evento da Memoria Partilha Dinamica
#define FILE_MAP_NAME		TEXT("mappedFile.txt")				// Nome do Ficheiro mapeado em memoria
//Estados de Jogo
#define CRIACAOJOGO		1
#define ASSOCIACAOJOGO	2
#define DECORRERJOGO	3
#define FINALJOGO		4
//Movimentos das Serpentes
#define CIMA			1
#define BAIXO			2
#define ESQUERDA		3
#define DIREITA			4

#define CRIARJOGO		5
#define JUNTARJOGO		6
#define ACTUALIZAMAPA	7

//Objectos
#define ALIMENTO		1 
#define GELO			2
#define GRANADA			3 
#define VODKA			4 
#define OLEO			5 
#define COLA			6 
#define O_VODKA			7 
#define O_OLEO			8 
#define O_COLA			9 

//Valores configuraveis por defeito
#define LINHAS			20
#define COLUNAS			20
#define TAMANHOSNAKE	3
#define NUMAUTOSNAKE	1
#define NUMOBJETOS		6


/* ----------------------------------------------------- */
/*  TIPOS												 */
/* ----------------------------------------------------- */
typedef struct {
	TCHAR username[SIZE_USERNAME];
	int codigoMsg;
}Msg;

typedef struct {
	char username[SIZE_USERNAME];
	int pontuacao;
	int direcao;
	int primeiroSegmento;
	int ultimoSegmento;
}Cobras;

typedef struct {
	int T;			//Tamanho inicial das Serpentes
	int A;			//Numero de Serpentes Autom�ticas
	int O;			//Numero de Objectos
	int N;			//Numero maximo de jogadores
	int L;			//Tamanho do Mapa em Linhas
	int C;			//Tamanho do Mapa em Colunas
}ConfigInicial;

typedef struct {
	int Tipo;		//Tipo de Objecto (1-Alimento, 2-Gelo, 3-Granada, 4-Vodka, 5-Oleo, 6-Cola, 7-OVodka, 8-OOleo, 9-OCola)
	int S;			//Segundos que fica no mapa
}Objecto;

typedef struct {
	Msg mensagem;					//Mensagem para utilizadores saberem o que h� de novo na mem�ria.
	int numClientes;				//Clientes actualmente ligados (esta var serve apenas para n�o deixar entrar mais utilizadores que MAXCLIENTES)
	int estadoJogo;
	TCHAR criador[SIZE_USERNAME];
	ConfigInicial config;
	Objecto objectos[NUMTIPOOBJECTOS];
}MemGeral;

