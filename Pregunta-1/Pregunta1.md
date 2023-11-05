**1.- Explique cual la relación de la taxonomía de Flynn y cada una de las librerías utilizadas hasta el momento: OpenMP, MPI, multiprocesing, System.Threading.Tasks**

**OpenMP (Open Multi-Processing):** Es una API para programación paralela multiproceso en sistemas de memoria compartida. Los programas que utilizan OpenMP entran en la categoría MIMD, ya que se ejecutan múltiples flujos de instrucciones (hilos) que pueden operar en diferentes partes de un conjunto de datos (flujos de datos).

OpenMP gestiona automáticamente el trabajo de dividir los datos entre los hilos y de sincronizar los resultados. Esto permite una explotación eficiente de la arquitectura de múltiples procesadores/cores para operaciones que pueden ser fácilmente paralelizadas como los bucles for.

**MPI (Message Passing Interface):** Es un estándar para la programación paralela en sistemas de memoria distribuida. Los programas MPI también son MIMD porque consisten en múltiples procesos (que pueden considerarse como flujos de instrucciones) que operan en su propia área de datos privada y se comunican a través del paso de mensajes.

**Multiprocessing (en Python):** El módulo Multiprocessing en Python proporciona una manera fácil y directa de crear procesos en lugar de hilos. Esto permite realizar cálculos paralelos de una manera que evita el Global Interpreter Lock (GIL) en Python, permitiendo que cada proceso ejecute código Python en paralelo en un núcleo de CPU separado.

Al igual que MPI, se clasifica como MIMD, con cada proceso ejecutando su propio flujo de instrucciones y trabajando en su propio flujo de datos. Aunque los procesos pueden compartir datos, cada proceso tiene su propio espacio de direcciones.

**System.Threading.Tasks (en .NET):** Es una biblioteca para la concurrencia y paralelismo en .NET, la cual facilita la creación de tareas que pueden correr en hilos separados. Al igual que OpenMP, se puede considerar dentro de la categoría MIMD, ya que puede haber múltiples tareas (flujos de instrucciones) ejecutándose en paralelo, potencialmente operando en diferentes conjuntos de datos.

En el modelo MIMD, la biblioteca System.Threading.Tasks permite que diferentes tareas se ejecuten en paralelo, lo que es particularmente útil para mejorar la escalabilidad y la capacidad de respuesta de las aplicaciones .NET, especialmente en aplicaciones de escritorio, servicios web y aplicaciones móviles donde se requiere mantener la interfaz de usuario ágil mientras se realizan operaciones intensivas en el fondo.