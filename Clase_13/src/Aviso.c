/*
 * Aviso.c
 * Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "Aviso.h"
#include "Cliente.h"
#include "validaciones.h"

static int generateNewId(void);
static Aviso* avi_newConParametros(int id, int rubro, char* text, int idCliente, int state);
static void avi_delete(Aviso* pAviso);
/**
 * \brief Crea un nuevo aviso.
 * \param int id, id del aviso.
 * \param int rubro, indica el rubro del aviso.
 * \param char* text, Puntero al espacio de memoria.
 * \param int idCliente, indica el id del cliente relacionado con el aviso.
 * \param int state, indica el estado actual del aviso (PAUSADO - ACTIVO).
 * \return devuelve un puntero al espacio de memoria del aviso.
 */
static Aviso* avi_newConParametros(int id, int rubro, char* text, int idCliente, int state)
{
	Aviso* pNewAd = NULL;
	if(id > 0 && rubro > 0 && text != NULL && idCliente > 0 && state >= 0 && state <= 1)
	{
		pNewAd = (Aviso*) malloc(sizeof(Aviso));
		if(pNewAd != NULL)
		{
			pNewAd->idAviso = id;
			pNewAd->rubro = rubro;
			strncpy(pNewAd->text,text, sizeof(pNewAd->text));
			pNewAd->idCliente = idCliente;
			pNewAd->estado = state;
		}
	}
	return pNewAd;
}
/**
 * \brief Borra un aviso (libera el espacio de memoria).
 * \param Aviso* pAviso, Es el puntero al espacio de memoria del aviso.
 */
static void avi_delete(Aviso* pAviso)
{
	if(pAviso!=NULL)
	{
		free(pAviso);
	}
}
/**
 * \brief Inicializa el array .
 * \param Aviso list[], Es el puntero al array.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_init(Aviso* list[], int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i] = NULL;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza el alta solo si el indice corresponde a un espacio vacio (isEmpty == 0)
 * \param Aviso* list[], Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente[], Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int id, indica el id del elemento.
 * \return (-1) Error / (0) Ok
 */
int avi_add(Aviso* list[], int len, Cliente* listCliente[], int lenCliente)
{
	int retorno = -1;
	int index;
	int idCliente;
	int indexCliente;
	Aviso buffer;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		cli_print(listCliente, lenCliente);
		if( utn_getNumberInt(&idCliente, "Ingrese el id del cliente que publicara el aviso: ", "Error.\n", 1, INT_MAX, 2) == 0 &&
			cli_findById(listCliente, lenCliente, idCliente, &indexCliente) == 0 &&
			avi_findFree(list, len, &index) == 0 && index < len &&
			utn_getNumberInt(&buffer.rubro, "Ingrese el rubro del aviso: ", "Rubro invalido.\n", 1, QTY_AVI, 2) == 0 &&
			utn_getText(buffer.text, "Ingrese el texto que desea publicar: ", "Texto invalido.\n", 2, LONG_TEXTO) == 0)
		{
			buffer.idAviso = generateNewId();
			list[index] = avi_newConParametros(buffer.idAviso, buffer.rubro, buffer.text, idCliente, ACTIVO);
			list[index]->idCliente = listCliente[indexCliente]->id;
			avi_showAds(list[index]);
			retorno = 0;
		}
		else
		{
			printf("El id seleccionado no existe.\n");
		}
	}
	return retorno;
}
/**
 * \brief Busca el elemento por id y se guarda su indice en un puntero.
 * \param Aviso* list[], Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return Retorna el indice
 */
int avi_findById(Aviso* list[], int len, int id, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i] != NULL && list[i]->idAviso == id)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Elimina el elemento que de encuentra en el indice recibido.
 * \param Aviso* list[], Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente[], Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_clientAndAdsRemove(Aviso* list[], int len, Cliente* listCliente[], int lenCliente)
{
	int retorno = -1;
	int idClienteRemove;
	int indexClienteRemove;
	int respuesta;
	int i;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		cli_print(listCliente, lenCliente);
		if( utn_getNumberInt(&idClienteRemove, "Ingrese el id del cliente que se quiere eliminar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			cli_findById(listCliente, lenCliente, idClienteRemove, &indexClienteRemove) == 0 && listCliente[indexClienteRemove] != NULL &&
			avi_printByIdCliente(list, len, listCliente, lenCliente, idClienteRemove) == 0 &&
			utn_getNumberInt(&respuesta, "El cliente y sus avisos se borraran �Desea continuar? (1- Si/2- No): ", "Error.\n", SI, NO, 2) == 0)
 		{
			if(respuesta == 1)
			{
				for (i = 0; i < len; i++)
				{
					if(list[i]->idCliente == idClienteRemove)
					{
						avi_delete(list[i]);
						list[i] = NULL;
					}
				}
				cli_remove(listCliente, lenCliente, idClienteRemove);
				retorno = 0;
			}
			else
			{
				printf("Se cancelo la eliminaci�n del cliente.\n");
			}
		}
		else
		{
			printf("No se puede borrar el cliente seleccionado.\n");
		}
	}
	return retorno;
}
/*
 * \ brief - Ordena el array por rubro.
 * \ param - Aviso* list[], recibe el array a utilizar.
 * \ param - int len, indica la longitud del array.
 * \ param - int order, indica el orden de los elementos. 1 en caso de ascendente y 0 en caso de descendente.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int avi_sortByRubro(Aviso* list[], int len, int order)
{
	int retorno = -1;
	int i;
	Aviso* aux;
	int flagSwap = 1;
	if(list != NULL && len > 0 && order >= 0 && order <= 1)
	{
		while(flagSwap)
		{
			flagSwap = 0;
			for (i = 0; i < (len - 1); i++)
			{
				if(	list[i] != NULL && list[i+1] != NULL &&
					((order == 1 &&
					list[i]->rubro < list[i+1]->rubro)
						||
					(order == 0 &&
					list[i]->rubro > list[i+1]->rubro)))
				{
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
					flagSwap = 1;
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Imprime los datos cargados.
 * \param Aviso* list[], Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente[], Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int avi_printByIdCliente(Aviso* list[], int len, Cliente* listCliente[], int lenCliente, int id)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && id > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i] != NULL && list[i]->idCliente == id)
			{
				printf("ID del cliente: %d - ID del aviso: %d - Texto: %s - Rubro: %d.\n",
						list[i]->idCliente, list[i]->idAviso, list[i]->text, list[i]->rubro);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Muestra un aviso.
 * \param Aviso* list[], Es el puntero al array.
 * \return (-1) Error / (0) Ok
 */
int avi_showAds(Aviso* pAd)
{
	int retorno = -1;
	char estadoAviso[20];

	if(pAd != NULL)
	{
		if(pAd != NULL)
		{
			if(pAd->estado == ACTIVO)
			{
				snprintf(estadoAviso, 20, "ACTIVO");
			}
			else
			{
				snprintf(estadoAviso, 20, "PAUSADO");
			}
			printf("ID cliente: %-1d - ID aviso: %-1d  - Texto: %-50s - Rubro: %-1d - Estado: %s.\n",
					pAd->idCliente, pAd->idAviso, pAd->text, pAd->rubro, estadoAviso);
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Busca un espacio libre en el array.
 * \param Aviso* list[], Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_findFree(Aviso* list[], int len, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex!= NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i] == NULL)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Busca un espacio ocupado en el array.
 * \param Aviso* list[], Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_findBusy(Aviso* list[], int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i] != NULL)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Imprime los avisos activos o pausados.
 * \param Aviso* list[], Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_mostrarAvisosPausadosOActivos(Aviso* list[], int len, int state)
{
    int retorno = -1;

    if(list != NULL && len > 0 && (state >= 0 || state <= 1))
    {
        for(int i=0;i<len;i++)
        {
            if(list[i] != NULL && list[i]->estado == state)
            {
            	avi_showAds(list[i]);
                retorno = 0;
            }
        }
    }
    return retorno;
}
/**
 * \brief Cambia el estado del aviso a pausado o activo segun corresponda.
 * \param Aviso* list[], Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente[], Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_changeStatus(Aviso* list[], int len, Cliente* listCliente[], int lenCliente, int state)
{
	int retorno = -1;
	int idChange;
	int indexChange;
	int indexCliente;
	int respuesta;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && (state >= 0 || state <= 1))
	{
		avi_mostrarAvisosPausadosOActivos(list, len, !state);
		if( ((state == 1 && utn_getNumberInt(&idChange, "Ingrese el ID del aviso que quiere reanudar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idChange, &indexChange) == 0 && list[indexChange]->estado != state &&
			cli_findById(listCliente, lenCliente, list[indexChange]->idCliente, &indexCliente) == 0 && cli_showClient(listCliente[indexCliente]) == 0)
				||
			(state == 0 && utn_getNumberInt(&idChange, "Ingrese el id del aviso que quiere pausar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idChange, &indexChange) == 0 && list[indexChange]->estado != state &&
			cli_findById(listCliente, lenCliente, list[indexChange]->idCliente, &indexCliente) == 0 && cli_showClient(listCliente[indexCliente]) == 0)) &&
			utn_getNumberInt(&respuesta, "�Desea cambiar el estado del aviso? (1- Si/2- No): ", "Error.\n", SI, NO, 2) == 0)
		{
			if(respuesta == 1)
			{
				list[indexChange]->estado = state;
				retorno = 0;
			}
			else
			{
				printf("Se cancelo el cambio de estado del aviso.\n");
			}
		}
		else
		{
			printf("No se puede cambiar el estado del ID seleccionado.\n");
		}
	}
	return retorno;
}
/**
 * \brief Realiza un alta forzada de un elemento.
 * \param Aviso* list[], Es el puntero al array.
 * \param int len, es el limite de array
 * \param int idCliente, indica el id del cliente.
 * \param int rubro, indica el rubro del aviso.
 * \param char* texto, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_altaForzada(Aviso* list[], int len, int idCliente, int rubro, char* texto)
{
    int retorno = -1;
    int index;
    Aviso* newAd;

    if(list != NULL && len > 0 && idCliente > 0 && rubro > 0 && texto != NULL)
    {
		if(avi_findFree(list, len, &index) == 0)
		{
			newAd = avi_newConParametros(generateNewId(), rubro, texto, idCliente, ACTIVO);
			list[index] = newAd;
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Imprime los avisos activos o pausados.
 * \param Aviso* list[], Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_mostrarAvisosPausadosOActivosPorId(Aviso* list[], int len, int state, int id)
{
    int retorno = -1;

    if(list != NULL && len > 0 && (state >= 0 || state <= 1))
    {
        for(int i=0;i<len;i++)
        {
            if(list[i] != NULL && list[i]->estado == state && list[i]->idCliente == id)
            {
            	avi_showAds(list[i]);
                retorno = 0;
            }
        }
    }
    return retorno;
}
/**
 * \brief Incrementa el id y lo retorna.
 * \return Retorna el id
 */
static int generateNewId(void)
{
	static int id = 0;

	id++;
	return id;
}
