/*
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3056 - Programacion de Microprocesadores
 * Date: 	2020/08/31
 * 
 * Manuel Rodas 21509
 * 
 * Laboratorio_3.2.cpp
 * Calculo de una serie como solucion de la parte dos del laboratorio 3
 */
 
#include <iostream>
#include <stdio.h>		//printf
#include <cmath>		//pow
#include <pthread.h>	

using namespace std;

void *calculos(void *argument){
    float *N;
    N = (float *)argument;
    

    // Se utiliza memoria de heap para asegurar que el espacio se memoria no se pierda cuando esta
	// función retorne y el hilo termine
    float *output;
    output = (float *)malloc(sizeof(float));
    *output = 1/((*N)*((*N) - 1));
    // Se convierte de float* a void* para el retorno
    return (void *)output;
}

int main(int nNumberofArgs, char* pszArgs[]){

    printf("\n\n");
    float N;
    float resultado = 0;

    printf("\n\n");

    cout << "Inicio del Laboratorio 3 Parte 2----------" <<  endl;

    printf("\n\n");

    cout << "Se evaluara la serie:     1((1) / n(n + 1)) " << endl;


    cout << "Ingrese el valor de n: " <<  endl;
    cin >> N;

    for (int i = 2; i < N; i++){
        pthread_t tid;
        pthread_attr_t attr;

        float v = (float) i;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        // Donde se guardará el puntero de retorno de cada hilo
        void *exit_value;

        pthread_create(&tid, &attr, calculos, (void *)&v);
        // Se unifica el thread, el cual nos dara su resultado en `exit_value`
        pthread_join(tid, &exit_value);

        // Se convierte de regreso de void* a float*
        float result = *((float *) exit_value);
        // Se debe liberar la memoria que se adquirió en el hilo
        free(exit_value);

        resultado += result;
    }

    cout << "El resultado de la serie evaluada es:   " << resultado << endl;

    return 0;
}