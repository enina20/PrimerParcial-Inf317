using System;
using System.Threading.Tasks;

class Program
{
    // Método para calcular factorial
    static long Factorial(int n)
    {
        long result = 1;
        for (int i = 2; i <= n; i++)
        {
            result *= i;
        }
        return result;
    }

    static void Main(string[] args)
    {
        // Número del cual queremos calcular el factorial
        int number = 4;

        // Crear y correr la tarea asíncrona para calcular el factorial
        Task<long> task = Task.Run(() => Factorial(number));

        // Esperar a que la tarea termine y obtener el resultado
        long factorial = task.Result;

        // Imprimir el resultado
        Console.WriteLine($"El factorial de {number} es {factorial}.");
    }
}
