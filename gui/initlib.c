#include <stdio.h>
#include <dlfcn.h>
#include "initlib.h"

void InitStructIA(StructIA *AIfunctions)
{
	AIfunctions->lib = NULL;
	AIfunctions->InitLibrary = NULL;
	AIfunctions->StartMatch = NULL;
	AIfunctions->StartGame = NULL;
	AIfunctions->EndGame = NULL;
	AIfunctions->EndMatch = NULL;
	AIfunctions->NextMove = NULL;
	AIfunctions->AttackResult = NULL;
	AIfunctions->Penalty = NULL;
}


void freeIA(StructIA *AIfunctions)
{
	dlclose(AIfunctions->lib);
}

int LoadAI(StructIA *AIfunctions, char* path)
{
printf("jambon jambon %s\n", path);
	 	if ((AIfunctions->lib=dlopen(path, RTLD_LAZY))==NULL)
        {
               
               fprintf(stderr, "%s\n", dlerror());
               //dlerror()
                return 0;
               
           }


               
            
    printf("lala1\n");
        if ((AIfunctions->InitLibrary=(pfInitLibrary)dlsym(AIfunctions->lib,"InitLibrary"))==NULL)
                return 0;
 printf("lala1\n");
        if ((AIfunctions->StartMatch=(pfStartMatch)dlsym(AIfunctions->lib,"StartMatch"))==NULL)
                return 0;
 printf("lala1\n");
        if ((AIfunctions->StartGame=(pfStartGame)dlsym(AIfunctions->lib,"StartGame"))==NULL)
                return 0;
       printf("lala1\n");
        if ((AIfunctions->EndGame=(pfEndGame)dlsym(AIfunctions->lib,"EndGame"))==NULL)
                return 0;
       printf("lala1\n");
        if ((AIfunctions->EndMatch=(pfEndMatch)dlsym(AIfunctions->lib,"EndMatch"))==NULL)
                return 0;
       printf("lala1\n");
        if ((AIfunctions->NextMove=(pfNextMove)dlsym(AIfunctions->lib,"NextMove"))==NULL)
                return 0;
       printf("lala1\n");
        if ((AIfunctions->AttackResult=(pfAttackResult)dlsym(AIfunctions->lib,"AttackResult"))==NULL)
                return 0;
 printf("lala1\n");
        if ((AIfunctions->Penalty=(pfPenalty)dlsym(AIfunctions->lib,"Penalty"))==NULL)
                return 0;
printf("jambon de parme\n");
    return 1;
}