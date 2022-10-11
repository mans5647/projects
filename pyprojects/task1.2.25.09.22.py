a = int(input("Enter number: ")) # putting num to stdin
if a > 0: # if positive, then adding 1
   a = a + 1
   print("Num:", a) 
elif a == 0: # else if equal to 0, then swapping by 10
     a = 10
     print("Num:", a)
else: # if negative
     print("Num: ", a - 2)
