import sys

if len(sys.argv) >= 2:
    filepath = sys.argv[1]
    pRead = open(filepath)
    tag = 1
    for line in pRead:
        if line != '\n':
            if line[0:len(line) - 1] == "sil " :
                line = line[0:len(line) - 1]
            if tag & 1:#tag is odd
                filepath = "..\\..\\model\\proto\\hmm_" + line[0 : len(line) - 1] + ".hmm"
                pWrite = open(filepath,'w')
                pWrite.write("~o <VecSize> 39 <MFCC_0_D_A>\n")
                pWrite.write("~h \"" + line[0:len(line) - 1] + "\"\n<BeginHMM>\n<NumStates> ")

            else :
                stateNum = int(line) * 3
                pWrite.write(str(stateNum) + "\n")
                for i in range(stateNum - 2):
                    pWrite.write("<State> " + str(i + 2) +  " <NumMixes> 2\n")
                    pWrite.write("<Mixture> 1 0.5\n")
                    pWrite.write('''<Mean> 39
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
<Variance> 39
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
<Mixture> 2 0.5
<Mean> 39
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0 0.0
<Variance> 39
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
''')
                pWrite.write("<TransP> " + str(stateNum) + "\n")
                pWrite.write("0.0 1.0 ")
                for i in range(stateNum-2):
                    pWrite.write("0.0 ")
                pWrite.write("\n")
                for i in range(stateNum -2):
                    for j in range(i + 1):
                        pWrite.write("0.0 ")
                    pWrite.write("0.5 0.5 ")
                    for j in range(stateNum - i - 3):
                        pWrite.write("0.0 ")
                    pWrite.write("\n")
                for i in range(stateNum-1):
                    pWrite.write("0.0 ")
                pWrite.write("0.0\n<EndHMM>")
            tag += 1