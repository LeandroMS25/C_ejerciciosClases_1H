/*
 * Informe.h
 * Author: Leandro Sobrino
 */

#ifndef INFORME_H_
#define INFORME_H_

#include "Cliente.h"
#include "Aviso.h"
#define OPTIONS_MAIN 9
#define OPTIONS_REPORT 6

int utn_showMainMenu(int* pOption, Aviso* list[], int len, Cliente* listCliente[], int lenCliente);
int utn_showReportMenu(int* pOption);
// INFORMES
int info_printClientes(Aviso* list[], int len, Cliente* listCliente[], int lenCliente); // Punto 7
int info_contarAvisosActivosPorId(Aviso* list[], int len, int id, int* pContador); // Punto 7
int info_contarAvisosPausadosPorId(Aviso* list[], int len, int id, int* pContador);
int info_contarAvisosPorId(Aviso* list[], int len, int id, int* pContador); // Punto 8. a
int info_printClientWithMoreAds(Aviso* list[], int len, Cliente* listCliente[], int lenCliente); // Punto 8. a
int info_contarAvisosPausados(Aviso* list[], int len); // Punto 8. b
int info_contarAvisosPorRubro(Aviso* list[], int len, int rubro, int* pContador); // Punto 8. c
int info_generarInformeDeRubro(Aviso* list[]); // Punto 8. c
int info_printClientWithMoreActivesAds(Aviso* list[], int len, Cliente* listCliente[], int lenCliente);
int info_printClientWithMoreInactivesAds(Aviso* list[], int len, Cliente* listCliente[], int lenCliente);

#endif /* INFORME_H_ */
