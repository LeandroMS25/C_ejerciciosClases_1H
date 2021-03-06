/*
 * Aviso.h
 * Author: Leandro Sobrino
 */
#ifndef AVISO_H_
#define AVISO_H_

#include "Cliente.h"
#define LONG_NAME 51
#define LONG_TEXTO 65
#define ACTIVO 1
#define PAUSADO 0
#define SI 1
#define NO 2
#define QTY_AVI 1000
typedef struct
{
	int idAviso;
	int rubro;
	char text[LONG_TEXTO];
	int idCliente;
	int estado;
}Aviso;

int avi_init(Aviso* list[], int len);
int avi_add(Aviso* list[], int len, Cliente* listCliente[], int lenCliente);
int avi_clientAndAdsRemove(Aviso* list[], int len, Cliente* listCliente[], int lenCliente);
int avi_changeStatus(Aviso* list[], int len, Cliente* listCliente[], int lenCliente, int state);
int avi_showAds(Aviso* pAd);
int avi_printByIdCliente(Aviso* list[], int len, Cliente* listCliente[], int lenCliente, int id);
int avi_mostrarAvisosPausadosOActivos(Aviso* list[], int len, int state);
int avi_mostrarAvisosPausadosOActivosPorId(Aviso* list[], int len, int state, int id);
int avi_findById(Aviso* list[], int len, int id, int* pIndex);
int avi_findFree(Aviso* list[], int len, int* pIndex);
int avi_findBusy(Aviso* list[], int len);
int avi_sortByRubro(Aviso* list[], int len, int order);
int avi_altaForzada(Aviso* list[], int len, int idCliente, int rubro, char* texto);

#endif /* AVISO_H_ */
