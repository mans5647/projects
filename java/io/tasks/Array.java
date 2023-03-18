package tasks;


import java.util.Scanner;
import static java.lang.System.*;


final class Array 
{
    public final static void main(String[] args)
    {
        Scanner size = new Scanner(System.in);

        
        
        int temp;
        System.out.print("Enter size of array : ");
        int n = size.nextInt();
        System.out.print("Enter K : ");
        int k = size.nextInt();
        System.out.print("Enter L : ");
        int l = size.nextInt();
        if (l > n | k <= 0)
        {
            return;
        }
        int arr[] = new int[n];
        for (int i = 0; i < n; ++i)
        {
            out.print(String.format("Enter element (%d): ", i));
            arr[i] = size.nextInt();
        }
        out.println("Before sort:: \n\n\n");
        for (int i = 0; i < n; i++)
        {
            out.print(arr[i] + "\t");   
        }

        out.println("\n\n\nAfter sort:: \n\n\n");
        
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j + 1] > arr[j])
                {
                    if (arr[j] == k || arr[j + 1] == l)
                    {
                        continue;
                    }
                    temp = arr[j + 1];
                    arr[j + 1] = arr[j];
                    arr[j] = temp;
                }   
            }
        }
        for (int i = 0; i < n; i++)
        {
            out.print(arr[i] + "\t");   
        }
        size.close();
    }
}
