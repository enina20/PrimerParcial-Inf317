using System;
using System.Threading.Tasks;

class Program
{
    // Método para calcular Pi utilizando el método de Montecarlo.
    static double CalculatePi(int samples)
    {
        Random random = new Random();
        int insideCircle = 0;

        for (int i = 0; i < samples; i++)
        {
            // Generar un punto aleatorio dentro del cuadrado [0,1] x [0,1]
            double x = random.NextDouble();
            double y = random.NextDouble();

            // Comprobar si el punto está dentro del cuarto de círculo
            if (x * x + y * y <= 1)
            {
                insideCircle++;
            }
        }

        // Calcular Pi como 4 veces la proporción de puntos dentro del círculo
        return (double)insideCircle / samples * 4;
    }

    static void Main(string[] args)
    {
        // Definir el número de muestras y tareas
        int samplesPerTask = 1000000;
        int taskCount = Environment.ProcessorCount;
        Task<double>[] tasks = new Task<double>[taskCount];

        // Iniciar las tareas para calcular Pi en paralelo
        for (int task = 0; task < taskCount; task++)
        {
            tasks[task] = Task.Run(() => CalculatePi(samplesPerTask));
        }

        // Esperar a que todas las tareas finalicen y combinar los resultados
        Task.WaitAll(tasks);
        double piEstimate = 0;
        foreach (var task in tasks)
        {
            piEstimate += task.Result;
        }
        piEstimate /= taskCount;

        // Imprimir la estimación de Pi
        Console.WriteLine($"Estimación de Pi con {samplesPerTask * taskCount} muestras: {piEstimate}");
    }
}
