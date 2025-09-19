[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/9quZgW1u)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20603816)
# Actividad - Vectores Paralelos

## El Problema: Registro de Atletas Olímpicos

La federación mundial de atletismo a solicitado una programa que permita gestionar los datos de los atletas de varios paises que participaron en las últimas olimpiadas. Se requiere un programa que les permita:

  1.- **Registrar a los atletas**: Se deberá almacenar el nombre de cada atleta, su país de origen, la disciplina que practica, su genero, y el número de medallas de oro que ganó.
  2.- **Buscar y mostrar la información de un atleta**: Dado el nombre de un atleta, el programa debe mostrar su país de origen y el número de medallas de oro.
  3.- **Calcular el total de medallas de oro del país**: El programa debe sumar todas las medallas de oro de los atletas registrados y mostrar el total por país.
  4.- **Encontrar al atleta con más medallas de oro**: El programa debe identificar y mostrar el nombre del atleta que obtuvo la mayor cantidad de medallas de oro.

Para poder realizar este programa se deberá realizar lo siguiente:

  * Se deberá investigar e implementar la lectura de archivos de texto (CSV) el cual tendrá la siguiente estructura:

```
Nombre,país,disciplina,genero,medallas
Pablo,México,Salto triple,M,2
Juan,EEUU,Marcha,M,1
Luisa,Canada,Salto de Altura,5
```

  * Se deberán utilizar cinco vectores paralelos para almacenar los datos:
    * Un vector para los nombres.
    * Un vector para los países de origen.
    * Un vector para la disciplina
    * Un vector para el género
    * Un vector para el número de medallas de Oro

  > **Nota**
  >
  > **Los vectores no serán dinámicos, por lo que se deberá calcular el tamaño de los vectores correspondientes a la cantidad de registros en el archivo, el cual puede tener cantidad de registros variables.**


### Requisitos de Implementación en C++

Su solución debe incluir:

  * Uso de vectores paralelos estáticos.
  * Lectura de archivos
  * La ruta del archivo se deberá leer desde la línea de comandos durante la ejecución del programa. Si el archivo no es includo como parámetro de entrada al programa, éste deberá preguntar.
  * Funciones claramente definidas para cada una de las tareas (registrar, buscar, calcular, encontrar el máximo, etc).

  * Manejo de entrada y salida del usuario.

  * Validación de la entrada. ¿Qué pasa si el usuario busca un atleta que no existe? ¿O ingresa datos inválidos?, etc.