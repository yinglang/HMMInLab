import sys

if len(sys.argv) == 2:
    ListPath = sys.argv[1]
    pListRead = open(ListPath, 'r')
    pWrite = open("..\\pro\\ref.mlf",'w')

    pWrite.write("#!MLF!#\n")
    for filepath in pListRead:
        filepath = filepath[0:len(filepath)-1]
        pRead = open(filepath,'r')
        pWrite.write("\"" + filepath + "\"\n")
        for line in pRead:
            pWrite.write(line)
        pWrite.write(".\n")
else:
    print "the parament must be one"