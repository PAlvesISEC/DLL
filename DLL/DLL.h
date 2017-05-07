//DLL.h
// O bloco ifdef seguinte � o modo standard de criar macros que tornam a exporta��o de
// fun��es e vari�veis mais simples. Todos os ficheiros neste projeto DLL s�o
// compilados com o s�mbolo DLL_IMP_EXPORTS definido. Este s�mbolo n�o deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// este ficheiro ir� ver as fun��es e vari�veis DLL_IMP_API como sendo importadas de uma
// DLL.

#include <windows.h>
#include <tchar.h>

//Definir uma constante para facilitar a leitura do prot�tipo da fun��o
//Este .h deve ser inclu�do no projeto que o vai usar (modo impl�cito)
#define TAM 256
// VINDO DO (.h) DO SERVIDOR 
#define SIZE_USERNAME		30									// Max chars do utilizador
#define TAM_BUFFER			20									// Tamanho de Buffer a utilizar no CLiente
#define MAXCLIENTES			4									// Maximo de Clientes 
#define MAXJOGADORES		4									// Max jogadores permitido
#define NUMTIPOOBJECTOS		10									// Tipo de objectos existentes
#define MAX_LINHAS			40									// Limite maximo de Linhas
#define MAX_COLUNAS			80
#define MIN_LINHAS			10
#define MIN_COLUNAS			10

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

//extern "C"   // Comentar para poder ser um ficheiro (.c) se n�o comentar tera de ser (.cpp)
//{
	//Vari�vel global da DLL
	extern DLL_IMP_API int nDLL;
	extern DLL_IMP_API HANDLE hMemoria;
	extern DLL_IMP_API HANDLE hSemMemoria;
	extern DLL_IMP_API HANDLE hEventoMemoria;
	extern DLL_IMP_API HANDLE hFicheiro;

	extern DLL_IMP_API char ponteiro[40960];

	//Fun��es a serem exportadas/importadas
	DLL_IMP_API int UmaString(void);
//}
