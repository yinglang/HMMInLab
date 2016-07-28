# coding=utf-8
import sys
if len(sys.argv) == 2:
    filepath = sys.argv[1]
    pRead = open(filepath,'r')#wordlist.txt
    pWrite = open("..\\pro\\hmmsdef.mmf",'w')
    time = 0
    for line in pRead:
        if line != '\n':
            line = line[0: len(line) - 1] #去除最后的\n
            if line == "sil ":
                line = line[0: len(line) - 1]
            print line
            everyHmmfilepath = "..\\..\\model\\hmm3\\hmm_" + line + ".hmm"
            pHmmRead = open(everyHmmfilepath,'r')
            if time == 0:
                pWrite.write(pHmmRead.read()) # read()读剩余全文
                pWrite.write("\n")
                time = 1
            else:
                for i in range(3):
                    pHmmRead.readline()
                pWrite.write(pHmmRead.read())
                pWrite.write("\n")
else :
    print "the agres must be one"