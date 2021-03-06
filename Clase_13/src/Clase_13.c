/*
 ============================================================================
 Name        : Clase_13.c
 Author      : Leandro Sobrino
 Description : Punteros
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aviso.h"
#include "Cliente.h"
#include "Informe.h"
#include "validaciones.h"
#define QTY_CLI 1000

int main(void)
{
	setbuf(stdout,NULL);
	Cliente* listCliente[QTY_CLI];
	Aviso* listAviso[QTY_AVI];
	int optionMain;
	int optionReport;

	cli_init(listCliente, QTY_CLI);
	avi_init(listAviso, QTY_AVI);

	// CLIENTES
	cli_altaForzada(listCliente, QTY_CLI,"Leandro","Sobrino","20-15665651-9");
	cli_altaForzada(listCliente, QTY_CLI,"Jorge","Suarez","20-31388898-4");
	cli_altaForzada(listCliente, QTY_CLI,"Nicolas","Ramos","23-38165869-3");
	cli_altaForzada(listCliente, QTY_CLI,"Laura","Ochoa","27-35098981-7");
	cli_altaForzada(listCliente, QTY_CLI,"Florencia","Ayala","27-40189698-8");

	// AVISOS
	avi_altaForzada(listAviso, QTY_AVI, 2, 1,"Vendo palio modelo 2005. No arranca.");
	avi_altaForzada(listAviso, QTY_AVI, 1, 7,"Vendo un Alexa que solo reconoce la voz en Aleman.");
	avi_altaForzada(listAviso, QTY_AVI, 2, 1,"Regalo caniche. No lo aguanto mas.");
	avi_altaForzada(listAviso, QTY_AVI, 3, 4,"Vendo guaymallen de fruta.");
	avi_altaForzada(listAviso, QTY_AVI, 4, 1,"Vendo guaymallen de fruta.");
	avi_altaForzada(listAviso, QTY_AVI, 3, 4,"Vendo guaymallen de fruta.");
	avi_altaForzada(listAviso, QTY_AVI, 3, 4,"Vendo guaymallen de fruta.");

	do
	{
		optionMain = 0;
		utn_showMainMenu(&optionMain, listAviso, QTY_AVI, listCliente, QTY_CLI);
		switch (optionMain)
		{
			case 1:
				if(cli_add(listCliente, QTY_CLI) == 0)
				{
					printf("El cliente se creo correctamente.\n");
				}
				break;
			case 2:
				if(cli_modify(listCliente, QTY_CLI) == 0)
				{
					printf("El cliente se modifico correctamente.\n");
				}
				break;
			case 3:
				if(avi_clientAndAdsRemove(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
				{
					printf("El cliente y sus avisos se borraron correctamente.\n");
				}
				break;
			case 4:
				if(avi_add(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
				{
					printf("El aviso se publico correctamente.\n");
				}
				break;
			case 5:
				if(avi_changeStatus(listAviso, QTY_AVI, listCliente, QTY_CLI, PAUSADO) == 0)
				{
					printf("El aviso se pauso correctamente.\n");
				}
				break;
			case 6:
				if(avi_changeStatus(listAviso, QTY_AVI, listCliente, QTY_CLI, ACTIVO) == 0)
				{
					printf("El aviso se reanudo correctamente.\n");
				}
				break;
			case 7:
				if(cli_sortByName(listCliente, QTY_CLI, 1) == 0 && info_printClientes(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
				{
					printf("La lista se mostro correctamente.\n");
				}
				break;
			case 8:
				if(utn_showReportMenu(&optionReport) == 0)
				{
					switch (optionReport)
					{
						case 1:
							info_printClientWithMoreAds(listAviso, QTY_AVI, listCliente, QTY_CLI);
							break;
						case 2:
							info_contarAvisosPausados(listAviso, QTY_AVI);
							break;
						case 3:
							info_generarInformeDeRubro(listAviso);
							break;
						case 4:
							if(info_printClientWithMoreActivesAds(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
							{
								printf("Se mostro correctamente.\n");
							}
							else
							{
								printf("No hay avisos activos.\n");
							}
							break;
						case 5:
							if(info_printClientWithMoreInactivesAds(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
							{
								printf("Se mostro correctamente.\n");
							}
							else
							{
								printf("No hay avisos pausados.\n");
							}
							break;
						default:
							break;
					}
				}
				break;
			case 9:
				printf("Adios");
				break;
		}

	}while(optionMain != OPTIONS_MAIN);
}
