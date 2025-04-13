**Sistema de Gestión de Tickets.**

---
Descripción:

Este sistema permite registrar y gestionar tickets ingresados por usuarios. Cada ticket contiene un ID, una descripción del problema, una prioridad (baja por defecto) y la hora de registro. El sistema organiza los tickets según su prioridad en colas separadas (Alta, Media y Baja) para garantizar una atención buena y segura.
---

Cómo compilar y ejecutar:

Este proyecto está desarrollado en lenguaje C y puede ser ejecutado fácilmente con herramientas como Visual Studio Code y el compilador gcc.

Requisitos previos:

Tener instalado Visual Studio Code

Instalar la extensión C/C++

Tener un compilador de C instalado

Pasos para compilar y ejecutar:

Descarga y descomprime el proyecto en una carpeta.

Abre el proyecto en VS Code

Ir a Archivo --> Abrir carpeta... y seleccionar la carpeta del proyecto(el nombre del proyecto fue creado con total seriedad)

Abre el archivo tarea1.c

En la terminal integrada, ejecutar:
```
------> gcc tarea1.c -o tarea.exe
```
Ejecuta el programa con:
```
------> ./tarea.exe
````
**Funcionalidades Implementadas:**

**Registrar nuevos tickets con ID, descripción, prioridad y hora.**

**Asignar una nueva prioridad a un ticket existente.**

**Mostrar todos los tickets pendientes organizados por prioridad.**

**Procesar (atender) el siguiente ticket según su prioridad.**

**Buscar un ticket por su ID.**

Posibles mejoras:

El ID tiene que ser un caracter numerico ya que el programa asume que es un numero de identificacion unico y no un tipo char
ademas la descripcion del ticket no puede superar los 1000 caracteres. 

**Ejemplo de uso**

```
1. Registrar un nuevo ticket
Opción seleccionada: 1) Registrar ticket
Ingrese el ID del ticket: 24
Ingrese la descripción del problema: El monitor no enciende.
El ticket es guardado con su hora de registro y una prioridad Baja por defecto.
```
```
2. Asignar prioridad
Opción seleccionada: 2) Asignar prioridad
Ingrese el ID del ticket al que desea cambiar la prioridad: 24
Ingrese la nueva prioridad (1 = Alto, 2 = Medio, 3 = Bajo): 1
El sistema mueve el ticket a la cola correspondiente y actualiza su prioridad.
```
```
3. Mostrar pendientes
Opción seleccionada: 3) Mostrar tickets pendientes
Se listan todos los tickets agrupados por prioridad, con sus detalles (ID, descripción, hora).
```
```
4. Procesar siguiente ticket
Opción seleccionada: 4) Procesar siguiente ticket
El sistema atiende el ticket más urgente (de prioridad Alta, luego Media, luego Baja) y lo elimina de la cola.
```