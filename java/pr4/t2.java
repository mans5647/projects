import java.util.Random;
import java.util.Scanner;
public class t2 {
    public static void main(String [] args)
    {
        Scanner s = new Scanner(System.in);
        System.out.printf("Enter M: ");
        int m = s.nextInt();
        System.out.printf("Enter N: ");
        int n = s.nextInt();
        int [][] arr = new int[m][n];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                arr[i][j] = new Random().nextInt(50);
            }
        }
        System.out.printf("Before sort: \n\n");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                System.out.printf("%d\n",arr[i][j]);
            }
        }
        int temp = 0;
        System.out.printf("After sort: \n\n");
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                temp = arr[i][j];
                arr[i][j] = arr[m - i - 1][n - i - 1];
                arr[m - i - 1][n - i - 1] = temp;
            }
        }

        
        
        
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                System.out.printf("%d\n",arr[i][j]);
            }
        }
    }
}
