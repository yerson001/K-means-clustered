# k-means-Clustered
## leer los datos hasta la mitad
[datos]:https://data.cityofnewyork.us/Transportation/2015-Yellow-Taxi-Trip-Data/ba8s-jw6u
## [datos]:https://data.cityofnewyork.us/Transportation/2015-Yellow-Taxi-Trip-Data/ba8s-jw6u

![test para la cola](IMG/001.png)
## los datos estan fuera del rango del buffer(1000,1000) no acepta negativos
![test para la cola](IMG/002.png)
## multiplicamos por -1 en X para que esta en nuestro rango  pero en Y esta en 40,***
![test para la cola](IMG/003.png)
## Otra prueba aumentando los grupos
![test para la cola](IMG/004.png)
## Ya que os datos no varian mucho hacemos la siguiente operacion
## En X = (-1)*data+(rand()%Ancho)
## EN Y = data+(rand()%Altura)
## hacemos clustered para 100 grupos
![test para la cola](IMG/005.png)

~~~
COMPILAR: g++ kmean.cpp -lsfml-graphics -lsfml-window -lsfml-system
~~~
~~~
EJECUTAR: ./a.out
~~~
con n = 30001703
![test para la cola](IMG/006.png)
