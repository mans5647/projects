import java.util.Scanner;
public class t1 {
    public static void main(String [] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.printf("Enter N : ");
        int n = sc.nextInt();
        System.out.printf("Enter K : ");        
        int k = sc.nextInt();
        int[] arr = new int[n];

        for (int i = 0; i < n; i++)
        {
            arr[i] = i+1;
        }
        int iter = 0;
        for (int i = 0; i < arr.length; ++i)
        {
            arr[i - iter] = arr[i + 1];
            if (iter == k)
            {
                break;
            }
            
            iter++;
        }

        for (int i : arr)
        {
            System.out.printf("Arr elem [%d] is %d\n", i, arr[i]);
        }
    }
}
