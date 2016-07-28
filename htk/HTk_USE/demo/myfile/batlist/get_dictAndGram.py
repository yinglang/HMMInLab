import sys
if len(sys.argv) >= 2:
    filename = sys.argv[1]
    pRead = open(filename,'r')
    pWrite = open("..\\pro\\dict.txt","w")
    pWrite2 = open("..\\pro\\gram.txt",'w')

    pWrite2.write("$WORD = ")
    lastword = ''
    for word in (pRead):
        if word != "sil \n":
            word = word[0 : len(word) - 1]
            newword = word.upper() + "   " + "[" + word + "]" + "    " + word + "\n"
            pWrite.write(newword)

            if lastword != '' :
                pWrite2.write(lastword.upper() + ' | ')
            lastword = word

    pWrite2.write(lastword.upper() + ";\n")

    pWrite.write("SENT-START          [] sil\n" + "SENT-END            [] sil\n")
    pWrite2.write("({SENT-START}[$WORD]{SENT-END})\n")

else:
    print "[error] : parament must be two"

