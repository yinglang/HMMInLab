import sys
import os
import re

if len(sys.argv) == 3:
    DoesExist = sys.argv[2]
    rewrite = 'y'
    if DoesExist == "has_exist":
        tempRead = open("..\\bate\hmmState.txt", 'r')
        temp = tempRead.readlines()
        if temp != "":
            print "the word segment is like that : "
            for ii in range(len(temp)/2):
                print temp[2 * ii][0:len(temp[2* ii]) - 1]," : ",temp[2 * ii+1][0:len(temp[2* ii + 1]) - 1]
            rewrite = raw_input("Do you want to rewrite hmmState ? (Y/N)")

    if rewrite == 'Y' or rewrite == 'y':
        filepath = sys.argv[1]
        pRead = open(filepath, 'r')
        wordlist = pRead.readlines()
        state = [""] * len(wordlist)
        #must use more than one char to initial,or can only get a alpha

        print "input the segement number(not state),like caozuo : 5 "
        print "print 'b' or 'B' to backspace to last word ."

        ij = 0
        while ij < len(wordlist):
            s = wordlist[ij]
            state[ij] = raw_input(s[0:len(s) - 1] + " : ",)

            while not (re.match(r"\d+$", state[ij]) and True or False ):
                #illeagal input
                if state[ij] == "B" or state[ij] == "b":
                    #backspace
                    if ij > 0 :
                        ij -= 1
                    s = wordlist[ij]
                    state[ij] = raw_input(s[0:len(s) - 1] + " : ", )
                else:
                    #avoid input is empty
                    print "please input a number : "
                    state[ij] = raw_input(s[0:len(s) - 1] + " : ", )
            #leagal input

            ij += 1

        pWrite = open("..\\bate\hmmState.txt", 'w')
        for i in range(len(state)):
            s = wordlist[i]
            pWrite.write(s + state[i] + '\n')
