package tests;

import java.util.Random;

/*
Дана матрица размера M × N. Найти номер ее столбца с наимень-шим 
произведением элементов и вывести данный номер, а также значение наименьшего произведения.
 */
class Current_Matrix
{
    public static void main(String args[])
    {
        Random r = new Random();
        int[][] arr = new int[10][10];
        long[] m_results = new long[10000];
        long multiply_result = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                arr[i][j] = r.nextInt(1000);
            }
        }
        int iter_cols = 0;
        int iterator = 0;
        for (int i = 0; i < 10; ++i)
        {
            if (arr[0][i + 1] > arr[0][i])
            
        }

        for (int i = 0; i < 10; i++)
        {
            System.out.println(m_results[i]);
        }
    }
}