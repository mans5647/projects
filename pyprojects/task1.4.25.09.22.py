letter = input("Please, enter a letter from A-Z: ") # puts letter in stdin

if  (letter.isdigit() == True): # optional checking for integer values
    print("Fatal: value should be character") # puts error
    exit()
elif (letter == 'a') or (letter == 'e') or (letter == 'i') or (letter == 'o') or (letter == 'u'): # checking for letter belongs to list of a,e,i,o,u
    print("Letter is vowel (Гласная)\n") # puts in stdout
elif letter == 'y': # checking for letter is 'y' which at once belongs to vowel and consonant sounds
    print("Letter has both sounds\n") # puts in stdout
else:
   
    print("Letter is consonant (Согласная)\n") # puts in stdout
