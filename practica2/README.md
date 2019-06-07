# PRÁCTICA 2 ALGORITMIA BÁSICA

## Ejecución del programa
Se puede ejecutar el programa con 2 algoritmos, el de ramificación y poda
solicitado en la práctica, y el algoritmo de fuerza bruta que mira todos los
nodos posibles. Esto se ha hecho para la posterior comparación de resultados y
comprobación de la corrección del algoritmo de ramificación y poda.

- Para ejecutar el programa con el algoritmo de ramificación y poda:
    `./transporte <nombre_fichero_entrada> <nombre_fichero_salida>`
- Para ejecutar el programa con el algoritmo de fuerza bruta:
    `./transporte <nombre_fichero_entrada> <nombre_fichero_salida> -fb`

## Compilación
- Para compilar, ejecutar el comando `make`.
- Para borrar los ficheros generados al compilar, ejecutar el comando `make clean`.

## Pruebas
Para la realización de las pruebas del algoritmo, se ha utilizado el fichero `problemas8000.txt`
de la carpeta `datos`, dicho fichero consiste en las 8000 instancias distintas del problema. Para
la comprobación de la corrección del algoritmo se ha ejecutado el programa con el algoritmo de
fuerza bruta y luego con el algoritmo de ramificación y poda y se ha comparado que los resultados
obtenidos fueran exactamente iguales (a excepción de los tiempos de ejecución que son menores
los obtenidos con el algoritmo de ramificación y poda). 