//DLL.h
// O bloco ifdef seguinte � o modo standard de criar macros que tornam a exporta��o de
// fun��es e vari�veis mais simples. Todos os ficheiros neste projeto DLL s�o
// compilados com o s�mbolo DLL_IMP_EXPORTS definido. Este s�mbolo n�o deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// este ficheiro ir� ver as fun��es e vari�veis DLL_IMP_API como sendo importadas de uma
// DLL.

#include <windows.h>
#include <tchar.h>
#include "TiposConstantes.h"

//Definir uma constante para facilitar a leitura do prot�tipo da fun��o
//Este .h deve ser inclu�do no projeto que o vai usar (modo impl�cito)

//Esta macro � definida pelo sistema caso estejamos na DLL (<DLL_IMP>_EXPORTS definida)
//ou na app (<DLL_IMP>_EXPORTS n�o definida) onde DLL_IMP � o nome deste projeto
//#ifdef DLL_EXPORTS

//**********************************************************************************
#ifdef DLL_EXPORTS   // VEIO DE -> PROP PROJ -> C++ -> LINHA COMANDO   -->  Est� l� o nome do proj + o EXPORT, copiar para aqui
//**********************************************************************************

#define DLL_IMP_API __declspec(dllexport)   // Deve ser acrescentado antes de cada declara��o de fun��o ****************
#else										// ou var global a usar fora da DLL, � para exportar		****************
#define DLL_IMP_API __declspec(dllimport)   // Se estiver na DLL faz o de sima, se n�o estiver faz este
#endif

//Vari�vel global da DLL
extern DLL_IMP_API HANDLE hMemoria;
extern DLL_IMP_API HANDLE hSemMemoria;
extern DLL_IMP_API HANDLE hEventoMemoria;
extern DLL_IMP_API HANDLE hFicheiro;
extern DLL_IMP_API MemGeral *vistaPartilhaGeral;

//Fun��es a serem exportadas/importadas
DLL_IMP_API int preparaMemoriaPartilhada(void);
DLL_IMP_API void preparaMapaJogo(MemGeral param);
DLL_IMP_API void inicializaMemoriaPartilhada(void);
DLL_IMP_API void esperaPorActualizacao(void);
DLL_IMP_API void leMemoriaPartilhada(MemGeral* param);
DLL_IMP_API void fechaMemoriaPartilhada(void);
DLL_IMP_API int Cria_Jogo(ConfigInicial param, TCHAR username1[SIZE_USERNAME]);
DLL_IMP_API void getMapa(MemGeral *param);
DLL_IMP_API void mudaDirecao(int direcao, int indice);
DLL_IMP_API int AssociaJogo(int numJogadores, TCHAR username1[SIZE_USERNAME], TCHAR username2[SIZE_USERNAME], int *indice);
DLL_IMP_API int IniciaJogo(TCHAR username[SIZE_USERNAME]);

