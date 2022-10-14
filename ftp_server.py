from ftplib import FTP
import os
import signal
import sys
def close_handler(address):
    address.close()
    exit(0)
def login_d():
    print("Enter your FTPs server IP address: ")
    temp = input()
    log = input("Enter login: ")
    pas = input("Enter password: ")
    try:
        addr = FTP(temp)
        addr.login(log, pas)
    except:
        print("Wrong username, incorrect IP addr or bad password. Check that you correctly entered a data and try again\n")
        exit()
    print("Successfully connected to server: {0} as {1}. Starting server mode:\n".format(addr,log))
    call_server(addr,log,pas)
def call_server(address, login, password):
    while True:
        try:
            command = str(input("Command prompt (h -- for help): "))
            if command == 'h':
                print(srv_mode_option_helper)
            elif command == '.' or command == 'mypath':
                get_current_dir(address)
            elif command == 'chdir':
                pa = sys.argv[1]
                try:
                    change_dir(address, pa)
                except Exception:
                    print("Incorrect name of directory\n")
            elif command == 'l' or command == 'list':
                list_data(address)
            elif command == 'r' or command == 'remove':
                pass
            elif command == 'u' or command == 'upload':
                pass
            elif command == 's' or command == 'stat':
                print("User: {0}\n".format(login))
                print("Server address: {0}\n".format(address))
            elif command == 'mk' or command == 'mkdir':
                dir_name = sys.argv[1]
                make_directory(address, dir_name)
            elif command == 'rm' or command == 'rmdir':
                dir_name = sys.argv[1]
                remove_dir(address, dir_name)
        except KeyboardInterrupt:
            close_handler(address)
#@@@@@@@@@
def make_directory(addr, pthname):
    new_dir = addr.mkd(pthname)
    print(new_dir)

def remove_dir(addr, pthname):
    addr.rmd(pthname)

def get_current_dir(address):
    path = address.pwd()
    print(path)
    
#
def change_dir(address,pathname):
    address.cwd(pathname)
#
 

def list_data(address):
    data = address.mlsd("READ")
    
usage = '''usage: ftp_server.py....[OPTION]..[ADDR]..-p..[PORT]...
            Options:
            1. CONNECTING KEYS:

                        -c or --connect ...[ADDRESS] -p ...[PORT]...:
                        EX: ftp.py --connect 000.0.0.1 -p 8888'''
            
srv_mode_option_helper = '''2. SERVER MODE KEYS:
                        
                            . or mypath | DESCR: returning address of currecnt working directory
                        
                            .. chdir ...[DIRECTORY]...| DESCR: moves to specified directory

                            l or list | DESCR: puts context of CURRENT directory

                            mkd or mkdir | DESCR: makes a new specified directory

                            rmd or rmdir | DESCR: remove specified directory

                            r or remove ...[FILENAME]..[FILENAME2]..[ETC.] | DESCR: removes FILES from server
                        
                            u or upload ..[FILENAME]..[FILENAME] | DESCR: uploads a new(s) file(s) to server
                        
                            s or stat [WHAT_YOU_WANT] | DESCR: gets server staticts. You can choose what you want to see\n'''

if len (sys.argv) <= 1:
    print(usage)
else:
    if len (sys.argv) >=2:
        argv_name_num1 = sys.argv[1]
        if argv_name_num1 == '--connect':
            login_d()
        