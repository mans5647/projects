try: # trying input
    value = float(input("Enter value of mass:")) # entering mass 
except ValueError: # exception ValueError, if value is not float
    print("Mass should be integer") # putting in to stdout 
    exit() # exiting
try: # trying input of action
    mass_n = int(input("Enter number of action:")) # entering action num
    match mass_n: # match_case
        case 1: # number of kg. There is nothing to do, just putting value in KG
            print("In kg:", value) # puts it 
        case 2: # value divided to milli in kgs
            value = value / 1000000
            print("In kg:",value) # puts it
        case 3: # value divided to gramme in kgs
            value = value / 1000
            print("In kg:", value) # puts it
        case 4:# value divided to kgs in tonne
            value = value / 1000 
            print("In kg:", value) # puts it
        case 5:# value divided to centners in kgs
            value = value / 100  
            print("In kg:", value) # puts it
except ValueError: # if number is not integer, then ValueError
    print("Fatal: number should be integer")
