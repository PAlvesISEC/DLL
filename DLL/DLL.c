
#include <windows.h>
#include "DLL.h"

//Definição da variável global
HANDLE hMemoria;
HANDLE hSemMemoria;
HANDLE hEventoMemoria;
HANDLE hFicheiro;
MemGeral *vistaPartilhaGeral;

void preparaMemoriaPartilhada(void) {

	hFicheiro = CreateFile(FILE_MAP_NAME, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hMemoria = CreateFileMapping(hFicheiro, NULL, PAGE_READWRITE, 0, SIZE_MEM_GERAL, NOME_MEM_GERAL);

	vistaPartilhaGeral = (MemGeral*)MapViewOfFile(hMemoria, FILE_MAP_ALL_ACCESS, 0, 0, SIZE_MEM_GERAL);

	hEventoMemoria = CreateEvent(NULL, TRUE, FALSE, EVNT_MEM_GERAL);
	hSemMemoria = CreateSemaphore(NULL, MAXCLIENTES, MAXCLIENTES, SEM_MEM_GERAL);

	if (hMemoria == NULL || hEventoMemoria == NULL || hSemMemoria == NULL) {
		_tprintf(TEXT("[Erro] Criação de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}
}

void preparaMapaJogo(MemGeral param) {

	for (int i = 0; i < MAXCLIENTES - 1; i++) {
		WaitForSingleObject(hSemMemoria, INFINITE);
	}

	for (int z = 0; z < param.config.C; z++) {
		vistaPartilhaGeral->mapa[0][z] = TEXT('#');
		vistaPartilhaGeral->mapa[param.config.L - 1][z] = TEXT('#');
		for (int j = 1; j < param.config.L - 1; j++) {
			if (z == 0 || z == param.config.C - 1) {
				vistaPartilhaGeral->mapa[j][z] = TEXT('#');
			}
			else
				vistaPartilhaGeral->mapa[j][z] = TEXT(' ');
		}
	}
	SetEvent(hEventoMemoria);
	ResetEvent(hEventoMemoria);
	ReleaseSemaphore(hSemMemoria, MAXCLIENTES, NULL);
}

void inicializaMemoriaPartilhada(void) {
	//Inicialização da Memoria Partilhada
	vistaPartilhaGeral->estadoJogo = CRIACAOJOGO;
}

void esperaPorActualizacao(void) {
	WaitForSingleObject(hEventoMemoria, INFINITE);
}

void leMemoriaPartilhada(MemGeral* param) {

	WaitForSingleObject(hSemMemoria, INFINITE);

	param->estadoJogo = vistaPartilhaGeral->estadoJogo;
	param->mensagem.codigoMsg = vistaPartilhaGeral->mensagem.codigoMsg;
	_tcscpy_s(param->mensagem.username, SIZE_USERNAME, vistaPartilhaGeral->mensagem.username);
	param->config.C = vistaPartilhaGeral->config.C;
	param->config.L = vistaPartilhaGeral->config.L;

	ReleaseSemaphore(hSemMemoria, 1, NULL);
}

void fechaMemoriaPartilhada(void) {
	CloseHandle(hMemoria);
	CloseHandle(hSemMemoria);
	CloseHandle(hEventoMemoria);
	UnmapViewOfFile(vistaPartilhaGeral);
}

void getMapa(MemGeral *param) {
	WaitForSingleObject(hSemMemoria, INFINITE);
	for (int i = 0; i < vistaPartilhaGeral->config.L; i++) {
		for (int j = 0; j < vistaPartilhaGeral->config.C; j++) {
			param->mapa[i][j] = vistaPartilhaGeral->mapa[i][j];
		}
	}
	ReleaseSemaphore(hSemMemoria, 1, NULL);
}

int Cria_Jogo(MemGeral param, int numJogadores) {
	for (int i = 0; i < MAXCLIENTES - 1; i++) {
		WaitForSingleObject(hSemMemoria, INFINITE);
	}
	if ((vistaPartilhaGeral->estadoJogo != CRIACAOJOGO)) {
		ReleaseSemaphore(hSemMemoria, MAXCLIENTES, NULL);
		return 0;
	}
	
	vistaPartilhaGeral->estadoJogo = ASSOCIACAOJOGO;
	vistaPartilhaGeral->config = param.config;
	vistaPartilhaGeral->mensagem.codigoMsg = param.mensagem.codigoMsg;
	_tcscpy_s(vistaPartilhaGeral->mensagem.username, SIZE_USERNAME, param.mensagem.username);
	_tcscpy_s(vistaPartilhaGeral->criador, SIZE_USERNAME, param.criador);
	vistaPartilhaGeral->vagasJogadores = param.config.N;

	SetEvent(hEventoMemoria);
	ResetEvent(hEventoMemoria);
	ReleaseSemaphore(hSemMemoria, MAXCLIENTES, NULL);
	return 1;
}