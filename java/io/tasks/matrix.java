package tasks;
import java.util.Random;
import java.util.Scanner;
import static java.lang.System.*;


public class matrix 
{
    public final static void main(String args[])
    {
        int m , n, match = 0;
        Scanner sc1 = new Scanner(System.in);
        System.out.print("Enter M: ");
        m = sc1.nextInt();

        System.out.print("Enter N: ");
        n = sc1.nextInt();



        Random rand = new Random();
        int [][] arr = new int[m][n];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                arr[i][j] = rand.nextInt(100);
            }
        }

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (arr[0][j] == arr[0][m - 1])
                {
                    match++;
                }
            }    
        }


        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                System.out.print(String.format("Element of arr[%d][%d] is %d\n", i, j, arr[i][j]));
            }
        }
        out.println("Matches : " + match);
        sc1.close();
    }
}
