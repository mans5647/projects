import hashlib
import uuid
import os
import sys
def regist():
    login = input("Enter your login : ")
    password = input("Enter your password : ")
    role = input("Enter your role : ")

    salt_for_password = uuid.uuid4().hex

    final_password = hashlib.sha256(password.encode() + salt_for_password.encode()).hexdigest()
    with open("./parols.txt", "a") as write:
        write.write(f"{login} {final_password} {salt_for_password} {role}\n")
    
    return menu("Successful registration!")

def log():
    login = input("Enter your login : ")
    password = str(input("Enter your password : "))
   

    with open("./parols.txt", "r") as Read:
        for x in Read.readlines():
            x = x.split()
            tmp_pass = hashlib.sha256(password.encode() + str(x[2]).encode()).hexdigest()
            if login in x[0]:
                if tmp_pass in x[1]:
                    if x[3] == 'admin':
                        admin(login)
                    elif x[3] == 'customer':
                        cust(login)
                    elif x[3] == 'seller':
                        seller(login)
                else:
                    print("Wrong password!")
                    break
            else:
                pass
    print("Incorrect credentials! \n")            


        
            
        
def admin(username: str):
    print(f"Welcome to control panel {username}\n")
    act = int(input("Enter action: 1 - change password ; 2 - log out "))
    match act:
        case 1:
            pass
        case 2:
            return menu("Logged out!")
        case _:
            return menu("Logged out!")
                
def cust(username: str):
    print("You are logged into the buyer's personal account. Functionality for this user role will appear here soon\n")
    print("Press any key to continue...")
    ex = sys.stdin.read(1)
    return menu("Logged out!")
var = ""
def seller(username: str):
    print("You have entered seller's personal account. Functionality for this user role will appear here soon\n")
    print("Press any key to continue...")
    ex = sys.stdin.read(1)
    return menu("Logged out!")



def menu(msg: str):
    if sys.platform == "linux":    
        os.system("clear")
    elif sys.platform == "win32":
        os.system("cls")
    if len(msg) == 0:
        pass
    print(f"{msg}\n")
    act = int(input("Enter action : 1 - login ; 2 - registration : " ))
    if act == 1:
        log()
    else:
        regist()

if __name__ == "__main__":
    menu("")