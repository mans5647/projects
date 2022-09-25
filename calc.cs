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
			string a_msg = Console.ReadLine();
			double a = Convert.ToDouble(a_msg);
			Console.Write("Enter a second number: ");
			string b_msg = Console.ReadLine();
			double b = Convert.ToDouble(b_msg);
			Console.Write("Enter a number of action: ");
			string acttoi = Console.ReadLine();
			int act_chosen = Convert.ToInt32(acttoi);
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
					c = Math.Pow(a,b);
					Console.WriteLine("result (pow) " +c);
			} else if (act_chosen == 6)
			{
					c = Math.Sqrt(a);
					Console.WriteLine("result (sqrt) " +c);
					Console.Write("Do you want perform sqrt action with B ? (y/n): ");
					string asrt = Console.ReadLine();
					if (asrt == "y" || asrt == "yes" || asrt == "Yes")
					{
						double c1 = Math.Sqrt(b);
						Console.WriteLine("result (sqrt) with b " +c1);
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
					Console.WriteLine("result (percent) from a % = " +c);
					Console.Write("Do you want perform 1 percent action with B ? (y/n): ");
					string asrt1 = Console.ReadLine();
					if (asrt1 == "y" || asrt1 == "yes" || asrt1 == "Yes")
					{      
					       	b = b / 100;
						b = b * 1;
						double c2 = b;
						Console.WriteLine("result (percent) from  b % = " +c2);
					} else if (asrt1 == "n" || asrt1 == "no" || asrt1 == "No") 
					{
						continue;
					} else
						continue;
			} else if (act_chosen == 8)
			{
					a = a * (b - 1);
					c = a;
					Console.WriteLine("result (fact) " +c);
			} else if (act_chosen == 9)
			{
				Console.Write("Exiting...");
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
