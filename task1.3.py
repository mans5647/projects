a = float(input("Enter a: ")) # Input a, 
b = float(input("Enter b: ")) # b,
c = float(input("Enter c: ")) # and c

if a<b<c: # checking for condition which pointed out in brackets
    a = a * 2 # multi a,
    b = b * 2 # b,
    c = c * 2 # and c
    print("A: ", a," - B: ",b, " - C: ", c) # putting in stdout
    exit()
else: # if condition has not been fitted
    a = a * (-1) # turn into nagative values a,
    b = b * (-1) # b,
    c = c * (-1) # and c
    print("Changing sign: ", "A: ", a," - B: ", b , "- C: ", c) # putting instdout
    exit()
