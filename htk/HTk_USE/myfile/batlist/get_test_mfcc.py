import sys
import os
if len(sys.argv) == 4:
    pWordlist = open(sys.argv[2],'r')

    pWrite = open(sys.argv[3],'w')
    for word in pWordlist:
        word = word[0:len(word) -1]
        for list in os.listdir(sys.argv[1] + '\\'+ word):
            l = len(list)
            if list[l-4:l] == "mfcc":
                path = os.path.join(sys.argv[1], word,list)
                pWrite.write(path + "\n")
