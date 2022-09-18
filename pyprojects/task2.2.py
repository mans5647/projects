num1 = float(input("Enter first number:")) # num 1 stdin
num2 = float(input("Enter second number: ")) # num 2 stdin
num3 = 0 # num 3 is result. Initially it is 0
action = input("Enter action for numbers: ") # user's action entry 
match action: # match_case
    case '+': # if user entered +, then 
        num3 = num1 + num2 # num1 and num2 adding together
        print("Add. of n1 and n2:", int(num3)) # and finally num3 putting
    case '-': # if user entered -, then
        num3 = num1 - num2 # from num1 substracting num2
        print("Subs. of n1 and n2:", int(num3)) # and finally num3 putting  
    case "*":# if user entered *, then
        num3 = num1*num2 # num1 multiply on num2
        print("Multi. of n1 and n2:", int(num3)) # and finally num3 putting
    case "/": # if user entered /, then
        num3 = num1 / num2 # num1 dividing on num2
        print("Div. (plain) of n1 and n2: ", int(num3)) # and finally num3 putting
    case "%": # if user entered %, then
        num3 = num1 % num2 # num1 dividing on num2 with remnant. If two numbers are normal putting 0
        print("Div. (MOD) of ", num3) # and finally num3 putting
    case "**": # if user entered **, then
        num3 = num1 ** num2 # num1 is powering on num2 
        print("Pow. of num1 and num2: ", int(num3)) # and finally num3 putting
