usage_msg = '''A simple weekday difinitor. 1 - monday, 2 - tuesday, 3 - wednesday, 4 - thursday, 5 - friday, 6 - saturday, 7 - sunday. Info will be putted into screen'''
print(usage_msg, "\n")
wd = int(input("Enter day of week: ")) # entering day of week number

match wd: # entering to match_case
    case 1: # if 1 from wd input
        print("Monday") # --------------------------------+
    case 2: # if 2 from wd input                          |
       print("Tuesday") #           PUTTING ONE OF THE 7  |
    case 3: # if 3 from wd input    CASES OF DAYS IN      |
        print("Webnesday") #        STANDARD OUTPUT       |
    case 4: # if 4 from wd input                          |
        print("Thursday") #          EXAMPLE:             |
    case 5: # if 5 from wd input     IF USER ENTERED 1,   |
        print("Friday") #            THEN PUTS "MONDAY"   |
    case 6: # if 6 from wd input                          |
        print("Saturday") #                               |
    case 7: # if 7 from wd input                          |
        print("Sunday") #_________________________________+
    case _:
        print("Day is not determined.")
