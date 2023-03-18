import sys
import os
import hashlib
import uuid
import msvcrt

roles = ["admin", "customer", "seller"] # roles

warnings = ["Wrong action!", "Not implemented!", "Format incorrect!", "Credentials are wrong!", "Role is undefined !"]

admin_oblig = ["EDIT passwords", "DELETE passwords", "DELETE users"]

logins = []

passwords = []


credents = []

def roleIsNotInList():
    return print("Role is not listed is roles list\n")

def reg():
    try:
        tmp = []
        tmp_log = str(input("Enter new login: "))
        tmp_pass = str(input("Enter new password: "))
        tmp_role = None
        int_choose_role = int(input("Choose role: (1) admin;; (2) customer;; (3) seller : "))
        
        match int_choose_role:
            case 1: 
                tmp_role = roles[0]
            case 2: 
                tmp_role = roles[1]
            case 3: 
                tmp_role = roles[2]
            case _:
                roleIsNotInList()
                reg()
        
        salt_psw = uuid.uuid4().hex
        
        f_login = tmp_log
        f_password = tmp_pass + salt_psw

        tmp.append(tmp_log)
        tmp.append(tmp_pass)
        tmp.append(tmp_role)

        credents.append(tmp)

        h1 = hashlib.sha256(f_login.encode())
        h2 = hashlib.sha256(f_password.encode() + salt_psw.encode())

        with open("./credentials.txt", "a") as reg_user:
            reg_user.write(f"{h1.hexdigest()} {h2.hexdigest()} {salt_psw} {tmp_role};\n")
        return menu("")
    except ValueError:


        if sys.platform == "win32":
            os.system("cls")


        elif sys.platform == "linux":
            os.system("clear")
        print(warnings[2])
        reg()

def auth() -> None:
    redir_role = None
    login = str(input("Enter login: "))
    password = str(input("Enter password: "))
    role = str(input("Enter role: "))

    for i in credents:
        if login in i[0]:
            if password in i[1]:
                if role in i[2]:
                    if role == roles[0]:
                        admin(login, password)
                    elif role == roles[1]:
                        customer()
                    elif role == roles[2]:
                        seller()
                else:
                    auth()
            else:
                print("Password does not match! \n")
                auth()
        else:
            print("Login incorrect! \n")
    
    return


def change(ad_login: str, ad_pas: str):
    on = True
    while on:
        os.system("cls")
        print("User\t\tPassword\t\tRole")
        for indiv in credents:
            print(f"{indiv[0]}\t\t{indiv[1]}\t\t{indiv[2]}\n")
        act = int(input("actions available: 1 - change password; 2 - delete users; 3 - add users: "))
        match act:
            case 1:
                user = str(input("Enter name of user: "))
                for x in credents:
                    if user in x[0]:
                        passwd = str(input(f"Enter new password for user `{user}` : ")) 
                        x[1] = passwd
                        break
                    else:
                        pass
            case 2:
                pass
            case 3:
                pass
            case 4:
                on = False
    return admin(ad_login, ad_pas)


def admin(login: str, password: str) -> None:
    os.system("cls")
    def_role = "Admin"
    print(f"Welcome {login} we are glad to see you again! \n")
    print(f"Admin rights are sample: {admin_oblig[0]}")
    c = int(input("Choose action: 1 - change pass 2 - log_out "))
    match c:
        case 1:
            change(login, password)
        case 2:
            return menu("Logged out! ")


def customer() -> None:
    os.system("cls")
    print("You are logged into the buyer's personal account. Functionality for this user role will appear here soon\n")
    print("Press any key to return back: ")
    ex = msvcrt.getch()
    return menu("Logged out! ")

def seller() -> None:
    os.system("cls")
    print("You have entered the personal account of the seller. Functionality for this user role will appear here soon\n")
    print("Press any key to return back: ")
    ex = msvcrt.getch()
    return menu("Logged out! ")

def menu(msg: str) -> None:
    if sys.platform == "win32":
        os.system("cls")
    elif sys.platform == "linux":
        os.system("clear")
    if len(msg) == 0:
        pass
    else:
        print(msg + '\n')
    print("Hello! You should be logged in system to managment products!\n")
    print("Choose action: \n")
    print("1. Register; \n")
    print("2. Login\n")
    print("3. Exit; \n")

    act = int(input(" >>> "))

    match act:
        case 1: 
            reg()
        case 2:
            auth()
        case 3:
            print("Goodbye!\n")
            exit(0)
        case _:
            menu(warnings[0])



if __name__ == "__main__":
    menu("")