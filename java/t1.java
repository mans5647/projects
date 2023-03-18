import java.util.*;
class t1
{
    public static void main(String args[])
    {
        int n, k;
        double result = 0.0, power;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter N: ");
        n = sc.nextInt();
        System.out.print("Enter K: ");
        k = sc.nextInt();
        
        for (int i = 1; i <= n; i++)
        {
            power = i;
            for (int j = 1; j < k; j++)
            {
                power *= i;
            }
            result+=power;
        }
        System.out.print("Result: "+result + '\n');
        sc.close();
    }   
}