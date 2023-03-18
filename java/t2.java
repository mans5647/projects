import java.util.Scanner;
class E
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number to check it power of 3: ");
        int num = sc.nextInt();
        while (num > 0)
        {
            if ((num % 3) == 0)
            {
                System.out.println("True");
                break;
            }
            else
            {
                System.out.println("False");
                break;
            }
        }
        sc.close();
    }
}