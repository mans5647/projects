import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;


class Provider
{
    private String Provider_Name;
    private String Provider_Country;
    private int Subscribtions_Id;
    
    private List <String> company_info = new ArrayList<String>();
    public final void set_data(String P_Name, String P_Country, int Subs_ID)
    {
        this.Provider_Name = P_Name;
        this.Provider_Country = P_Country;
        this.Subscribtions_Id = Subs_ID;
        return; 
    }

    public final String Get_Provider_Name()
    {
        return this.Provider_Name;
    }

    public final String Get_Provider_Country()
    {
        return this.Provider_Country;
    }

    public final int Get_Subs_Id()
    {
        return this.Subscribtions_Id;
    }

    public void ShowData()
    {
        out.printf("Provider's name : %s\n", this.Provider_Name);
        out.printf("Provider's country : %s\n", this.Provider_Country);
        out.printf("Foreign key of Subscribtions types : %d\n\n", this.Subscribtions_Id);
        return;
    }
    public int Add_Data()
    {
        int return_value = 0;
        Scanner s = new Scanner(System.in);
        out.printf("You can add information to a provider. This is will be useful \n");
        out.printf("Choose what do you want to add to this provider\n");
        out.printf("1. Info about company foundation \n");
        out.printf("2. Companions\n");
        out.printf("Choose one: ");
        int act = s.nextInt();
        switch (act)
        {
            case 1:
                Add_Info_Ab_Company();
                break;
            default:
                return_value = 1;
                break;
        }
        return return_value;
    }

    private boolean Delete_Data()
    {
        final String msg = "Searching for data and removes it";
        final String not_found = "Not found";
        final String Successful = "Removed item ";
        out.printf("%s\n\n", msg);
        Scanner s = new Scanner(System.in);
        out.printf("Enter pattern : ");
        String search_pattern = s.nextLine();
        if (company_info.contains(search_pattern))
        {
            company_info.remove(search_pattern);
            out.printf("%s '%s' \n", Successful, search_pattern);  
            return true;
        }
        out.printf("%s ` %s ` in company info\n", not_found, search_pattern);
        return false;
    }


    private void Add_Info_Ab_Company()
    {
        Scanner sc = new Scanner(System.in);
        
        out.printf("Add some information about provider `%s'\n\n", this.Provider_Name);
        
        int strings_ = 10; // by default
        String line = "";
        int num = 0;
        while (strings_ > 0)
        {
            out.printf("L (%d): ",num++);
            line = sc.nextLine();
            if (line.isEmpty())
            {
                break;
            }
            out.printf("\n\n");
            company_info.add(line);
            out.printf("Line remaining: %d\n", --strings_);

        }
        return;
    }

    private void Show_add_Info()
    {
        for (int i = 0; i < company_info.size(); i++)
        {
            out.println("Row " + i + ": " + company_info.get(i));
        }
        return;
    }
    public void user_begin_invoke()
    {
        Scanner s = new Scanner(System.in);
        int action = 0;
        while (action != 4)
        {
            out.printf("Control menu for provider '%s' \n", this.Provider_Name);
            out.printf("1. Add information\n");
            out.printf("2. Delete info\n");
            out.printf("3. Exit\n");
            action = s.nextInt();
            switch (action)
            {
                case 1: 
                    int ret = Add_Data();
                    if (ret == 1)
                    {
                        out.println("------- FAILURE -------");    
                    }
                    else
                    {
                        out.println("------- OK -------");
                    }
                    break;
                case 2: 
                    boolean IsSuccess = Delete_Data();
                    if (IsSuccess)
                    {
                        out.println("------- OK -------");
                    }
                    else
                    {
                        out.println("------- FAILURE -------");
                    }
                    break;
                case 3:
                    Show_add_Info();
                    break;
            }
        }
        s.close();
    }
}

class User 
{
    private String Username;
    private String PhoneNumber;
    private long Amount;
    private String information;
    private String EmailAddr;

    

    public String Get_Name()
    {
        return this.Username;
    }
    public String Get_PhoneNum()
    {
        return this.PhoneNumber;
    }

    public long Get_Amount()
    {
        return this.Amount;
    }

    public void Set(String UserNm)
    {
        this.Username = UserNm;
    }

    public void Set_Phone(String Phonenumber)
    {
        this.PhoneNumber = Phonenumber;
    }

    public void Set_Amount(long __amount__)
    {
        this.Amount = __amount__;
    }

    public void Set_Initial(String arg1, String arg2, long arg3)
    {
        this.Username = arg1;
        this.PhoneNumber = arg2;
        this.Amount = arg3;
        this.information = "";
        this.EmailAddr = "";
    }
    private void rewrite_all(String a1, String a2, long Amnt, String add, String email)
    {
        this.Username = a1;
        this.PhoneNumber = a2;
        this.Amount = Amnt;
        this.information = add;
        this.EmailAddr = email;
    }

    private void Add_Info()
    {
        long Times = 240;
        String Sym = "";
        Scanner sc = new Scanner(System.in);
        while (sc.hasNextLine())
        {
            Sym = sc.nextLine();
            this.information += Sym + '\n';
            long length = Sym.length();
            Times-=length;
            if (Sym.isEmpty())
            {
                break;
            }
            out.printf("Character left (%d): ", Times);
            if (Times == 0)
            {
                break;
            }
            
        }
        return;
    }


    private void Show_Data()
    {
        out.printf(" * Username: %s\n", this.Username);
        out.printf(" * Phone number:  %s\n", this.PhoneNumber);
        out.printf(" * Amount ($) : %d\n", this.Amount);
        out.printf(" * Additional information : %s\n", this.information);
        out.printf(" * Email address : %s\n", this.EmailAddr);
        return;
    }

    public final void Menu()
    {   
        int change_direction = 0; // No actiona
        Scanner sc = new Scanner(System.in);
        while (change_direction != 5)
        {    
            
            out.printf("\nUser accound modification; \n");
            out.printf("1. Change name\n");
            out.printf("2. Rewrite all data\n");
            out.printf("3. Add user additional information\n");
            out.printf("4. Show current user data\n");
            out.printf(": (5 - to terminate)");
            change_direction = sc.nextInt();
            switch (change_direction)
            {
                case 1:
                    Scanner r = new Scanner(System.in);
                    out.print("\n\nEnter new name: ");
                    String new_name = r.nextLine();
                    Set(new_name);
                    break;
                case 2:
                    sc.reset();
                    Scanner er = new Scanner(System.in);
                    out.printf("Enter name: ");
                    String name = er.nextLine();
                    out.printf("Enter phone: ");
                    String Phone = er.nextLine();
                    out.printf("Enter amount ($): ");
                    long amount = er.nextLong();
                    er.nextLine();
                    out.printf("Enter additional info: ");
                    String add = er.nextLine();
                    out.printf("Enter email: ");
                    String email = er.nextLine();
                    rewrite_all(name, Phone, amount, add, email);
                    break;
                case 3:
                    Add_Info();
                    break;
                case 4:
                    Show_Data();
                    break;
            }
        }
        
    }
}


class Invoke
{
    public static void main(String[] args) throws Exception
    {
        out.printf("1 - provider 2 - user\n");
        int mode = 0;
        Provider new_prov = new Provider();
        User user = new User();
        Scanner sc = new Scanner(System.in);
        mode = sc.nextInt();
        if (mode == 1)
        {
            Scanner f = new Scanner(System.in);
            out.printf("Enter data for Provider : \n\n");
            out.printf("Enter provider's name: ");
            String P_name = f.nextLine();
            out.printf("Enter provider's country: ");
            String P_country = f.nextLine();
            out.printf("Enter provider's subs fk : ");
            int Subs_id = f.nextInt();
            new_prov.set_data(P_name, P_country, Subs_id);
            new_prov.ShowData();
            out.printf("Menu: ");
            new_prov.user_begin_invoke();
        }
        else if (mode == 2)
        {
            Scanner us = new Scanner(System.in);
            out.printf("Enter name: ");
            String name = us.nextLine();
            out.printf("Enter phone: ");
            String Phone = us.nextLine();
            out.printf("Enter amount ($): ");
            long amount = us.nextLong();
            user.Set_Initial(name, Phone, amount);
            user.Menu();
            us.close();
        }
        sc.close();
        
        
    }
}