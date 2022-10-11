import sys
usage_message = '''wcn stands for "Word Count New" that implies a new style of old wc in Unix-like operating systems
                usage: wcn [OPTION] [FILE]. All available options are represented below. 
                1. without options -- by default counts CHARS, WORDS, LINES, SPACES, TABS
                2. ..-c.. or ..--chars.. >  counts ONLY characters
                3. ..-w.. or ..--words.. > counts ONLY words
                4. ..-l.. or ...--lines... > counts ONLY lines
                5. ..-ss or ...--specsym... > counts ONLY specsymbols
                6. ..-sp or ...--spaces... > counts ONLY spaces
                7. ..-t or ...--tabs... > counts ONLY tabulations
                8. ..-f.. or --cffile... or --count-from-file > rapidly running on FILE and count things of  .. 1. point

                THIS PROGRAM MADE WITHOUT ANY WARRANTY WITH EDUCATING PURPOSES AND MAY BE USED ANY OF PEOPLE.'''
handler_error = '''is not recognized in any of represented forms. Try: wcn --help or wcn -h to get short reference about this program'''
state_in = 1
state_out = 0
state = state_out
def wc_words():
    wrd_st_in = 1
    wrd_st_out = 0
    wrd_state = 1
    words = 0
    che = 0
    while True:
        c = sys.stdin.read(1)
        che+=1
        if c == ' ' or c == '\t' or c == '\n':
            wrd_state = wrd_st_out
        elif wrd_state == wrd_st_out:
            wrd_state = wrd_st_in
            words+=1
        if c == '':
            break
    print("Words: {}".format(words))
# def wc_line(str):
# def wc_char(str):
# def wc_specsym(str):
# def wc_spaces(str):
# def wc_tabs(str):
main_txt = 0
chars = words = lines = ss = spaces = tabs = 0
if len (sys.argv) <= 1:
    while True:
        c = sys.stdin.read(1)
        chars+=1
        if c == '\n':
            lines+=1
        if c == ' ':
            spaces+=1
        if c == '\t':
            tabs+=1
        if c == ' ' or c == '\t' or c == '\n':
            state = state_out
        elif state == state_out:
             state = state_in
             words+=1
        if c == '':
            break
    print("CHARS: {} | WORDS: {} | LINES: {} | SPACES: {} | TABS {}".format(chars, words, lines, spaces, tabs))
else:
    if len (sys.argv) >= 1:
        param_name = sys.argv[1]
        if (sys.argv[1]) == '-h' or (sys.argv[1]) == '--help':
            print(usage_message)
        elif (sys.argv[1]) == '-w' or (sys.argv[1]) == '--words':
            wc_words()
        else:
            print(sys.argv[1],handler_error)
