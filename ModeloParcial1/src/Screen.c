/*
 * Screen.c
 *
 *  Created on: 29 sept. 2020
 *      Author: Leandro
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "Screen.h"
#include "validaciones.h"

static int generateNewId(void);
/**
 * \brief Inicializa el array .
 * \param Screen list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int scr_init(Screen* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza el alta solo si el indice corresponde a un espacio vacio (isEmpty == 0)
 * \param Screen* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, indica el id del elemento.
 * \return (-1) Error / (0) Ok
 */
int scr_add(Screen* list, int len)
{
	int retorno = -1;
	int index;
	Screen buffer;

	if(list != NULL && len > 0)
	{
		if( scr_findFree(list, len, &index) == 0 && index < len &&
			utn_getString(buffer.name, "Ingrese el nombre de la pantalla: ", "Nombre invalido.\n", 2, LONG_NAME - 1) == 0 &&
			utn_getNumberInt(&buffer.type, "Ingrese el tipo de la pantalla (0- LED / 1- LCD): ", "Tipo invalido.\n", 0, 1, 2) == 0 &&
			utn_getNumberFloat(&buffer.price, "Ingrese el precio de la publicidad en la pantalla: ", "Precio invalido.\n", 1, FLT_MAX, 2) == 0 &&
			utn_getString(buffer.address, "Ingrese la direcci�n de la pantalla: ", "Direccion invalida.\n", 2, LONG_NAME - 1) == 0)
		{
			buffer.isEmpty = 0;
			buffer.id = generateNewId();
			list[index] = buffer;
			retorno = 0;
		}
		else
		{
			printf("No hay espacios libres para dar de alta.");
		}
	}
	return retorno;
}
/**
 * \brief Modifica datos si el indice no est� vacio.
 * \param Screen* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Screen aux, recibe un dato del tipo Screen.
 * \param int index, es el indice donde se cargara el elemento.
 * \return (-1) Error / (0) Ok
 */
int scr_modify(Screen* list, int len)
{
	int retorno = -1;
	Screen buffer;
	int idModify;
	int indexModify;

	if(list != NULL && len > 0)
	{
		scr_print(list, len);
		if( utn_getNumberInt(&idModify, "Ingrese el id del elemento que quiere modificar: ", "\nError", 1, INT_MAX, 2) == 0 &&
			scr_findById(list, len, idModify, &indexModify) == 0 &&
			utn_getString(buffer.name, "Ingrese el nombre de la publicidad: ", "Nombre invalido.\n", 2, LONG_NAME - 1) == 0 &&
			utn_getNumberInt(&buffer.type, "Ingrese el tipo de la pantalla (0- LED / 1- LCD): ", "Tipo invalido.\n", 0, 1, 2) == 0 &&
			utn_getNumberFloat(&buffer.price, "Ingrese el el precio de publicidad en la pantalla", "Precio invalido.\n", 1, FLT_MAX, 2) == 0 &&
			utn_getString(buffer.address, "Ingrese la direcci�n de la publicidad en la pantalla", "Direccion invalida.\n", 2, LONG_NAME - 1) == 0)
		{
			buffer.id = list[indexModify].id;
			buffer.isEmpty = 0;
			list[indexModify] = buffer;
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Busca el elemento por id y se guarda su indice en un puntero.
 * \param Screen list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return Retorna el indice
 */
int scr_findById(Screen* list, int len, int id, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].id == id)
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
 * \param Screen* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int index, es el indice donde se cargara el elemento.
 * \return (-1) Error / (0) Ok
 */
int scr_remove(Screen* list, int len)
{
	int retorno = -1;
	int idRemove;
	int indexRemove;

	if(list != NULL && len > 0)
	{
		scr_print(list, len);
		if( utn_getNumberInt(&idRemove, "Ingrese el id del elemento que quiere dar de baja: ", "\nError", 1, INT_MAX, 2) == 0 &&
			scr_findById(list, len, idRemove, &indexRemove) == 0)
		{
			list[indexRemove].isEmpty = 1;
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \ brief - Ordena el array por nombre.
 * \ param - Screen* list, recibe el array a utilizar.
 * \ param - int len, indica la longitud del array.
 * \ param - int order, indica el orden de los elementos. 1 en caso de ascendente y 0 en caso de descendente.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int scr_sortByName(Screen* list, int len, int order)
{
	int retorno = -1;
	int i;
	Screen aux;
	int flagSwap = 1;
	if(list != NULL && len > 0)
	{
		while(flagSwap)
		{
			flagSwap = 0;
			for (i = 0; i < (len - 1); i++)
			{
				if(	(order == 1 &&
					strncmp(list[i].name, list[i+1].name,LONG_NAME) > 0) ||
					(order == 0 &&
					strncmp(list[i].name, list[i+1].name,LONG_NAME) < 0))

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
 * \param Screen* list, Es el puntero al array
 * \param int len, es el limite de array
 * \return (-1) Error / (0) Ok
 */
int scr_print(Screen* list, int len)
{
	int retorno = -1;
	char strType[8];
	int i;

	if(list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				if(list[i].type == 0)
				{
					sprintf(strType, "LED");
				}
				else
				{
					sprintf(strType, "LCD");
				}
				printf( "Id: %d - Nombre: %s - Tipo: %s - Precio: %.2f - Direcci�n: %s.\n",list[i].id , list[i].name,
											strType, list[i].price, list[i].address);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Busca un espacio libre en el array.
 * \param Screen* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int scr_findFree(Screen* list, int len, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex!= NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 1)
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
 * \param Screen* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int scr_findOccupied(Screen* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				retorno = 0;
				break;
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
