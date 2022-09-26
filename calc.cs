using System;

namespace Calc
{
	class Prog
	{
		static void  Main(string[] args)
		{
			double c = 0.0;
			string info = "This prog manipulating with numbers";
			string usage_act = "1 - add two numbers, 2 - substact one from second, 3 - multiply, 4 - division, 5 - power one, 6 - sqrt, 7 - 1 percent, 8 - fatorial N, 9 - quit, 10 - get this message ";
			Console.WriteLine(info, "\n");
			Console.WriteLine(usage_act, "\n");
			while (true) 
		{
		try
		{
			Console.Write("Enter a first number: ");
			double a = Convert.ToDouble(Console.ReadLine());
			Console.Write("Enter a second number: ");
			double b = Convert.ToDouble(Console.ReadLine());
			Console.Write("Enter a number of action: ");
			int act_chosen = Convert.ToInt32(Console.ReadLine());
			if (act_chosen == 1) 
			{
				c = a + b;
					Console.WriteLine("result (add) " +c);
			} else if (act_chosen == 2)
			{		c = a - b;
					Console.WriteLine("result (sub) " +c);
			} else if (act_chosen == 3)
			{
					c = a * b;
					Console.WriteLine("result (mul) " +c);
			} else if (act_chosen == 4)
			{
					c = a / b;
					Console.WriteLine("result (div) " +c);
			} else if (act_chosen == 5)
			{
				double res = 1;
				 Console.Write("Enter a power to increase the number: ");
       				int orig_pow = Convert.ToInt32(Console.ReadLine());
				for (int i = 1; i <= orig_pow; i++)		
					{
						res = res*a;

					}
				Console.WriteLine("result (pow) on a: "+res);
				Console.Write("Do you want perform such action with B? (y/n): ");
				string asrt2 = Console.ReadLine();
				if (asrt2 == "y" || asrt2 == "yes" || asrt2 == "Yes")
				{
					double res2 = 1;
					Console.Write("Enter a power to increase the number: ");
					int orig_pow2  = Convert.ToInt32(Console.ReadLine());
					for (int j = 1; j<= orig_pow2; j++)
					{
						res2 = res2 * b;	
					}
					Console.WriteLine("result (pow) on b: "+res2);
				} else if (asrt2 == "n" ||asrt2 == "no" || asrt2 == "No" )
				{
					continue;
				} else
				{
					continue;
				}
			} else if (act_chosen == 6)
			{
					c = Math.Sqrt(a);
					Console.WriteLine("result (sqrt): " +c);
					Console.Write("Do you want perform such action with B? (y/n): ");
					string asrt = Console.ReadLine();
					if (asrt == "y" || asrt == "yes" || asrt == "Yes")
					{
						double c1 = Math.Sqrt(b);
						Console.WriteLine("result (sqrt) with b: " +c1);
					} else if (asrt == "n" || asrt == "no" || asrt == "No")
					{
						continue;
					} else
						continue;
			} else if (act_chosen == 7)
			{
					a = a / 100;
					a = a * 1;
					c = a;
					Console.WriteLine("result (percent) from a % : " +c);
					Console.Write("Do you want perform such action with B? (y/n): ");
					string asrt1 = Console.ReadLine();
					if (asrt1 == "y" || asrt1 == "yes" || asrt1 == "Yes")
					{      
					       	b = b / 100;
						b = b * 1;
						double c2 = b;
						Console.WriteLine("result (percent) from  b % : " +c2);
					} else if (asrt1 == "n" || asrt1 == "no" || asrt1 == "No") 
					{
						continue;
					} else
						continue;
			} else if (act_chosen == 8)
			{
				double fact = 1;
				for (int h = 1; h <= a; h++)
				{
					fact = fact * h;
				}
					Console.WriteLine("result (fact): " +fact);
					Console.Write("Do you want perform such action with B? (y/n): ");
					string asrt3 = Console.ReadLine();
					if (asrt3 == "y" || asrt3 == "yes" || asrt3 == "Yes")
					{
						double fact2 = 1;
						for (int y = 1; y <= b; y++)
						{
							fact2 = fact2 * y;
						}
						Console.WriteLine("result (fact) for b: "+fact2);
					} else if (asrt3 == "n" ||  asrt3 == "no" || asrt3 == "No")
					{
						continue;
					} else
						continue;
			} else if (act_chosen == 9)
			{
				Console.WriteLine("Exiting...");
				break;
			} else if (act_chosen == 10)
			{
					Console.WriteLine(info,"\n");
					Console.WriteLine(usage_act,"\n");
			}
		   }	
		catch
		{
			Console.WriteLine("Exiting...");
			break;
		}
		}
		}
	}
}
