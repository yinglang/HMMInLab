import sys

def isfile(path):
    if path[len(path) -5] == '.':
        return 1
    else: return 0

def complement(path):
    length = len(path) - 5#.wav\n five bit
    tag = 0
    the_word = ''
    for i in range(length) :
        position = length - i - 1
        if path[position] == '\\':
            tag = tag + 1
            if tag == 2:
                newpath1 = path[position: length]
                lastposition = position
            if tag == 5:
                newpath2 = '..\..' + path[position: lastposition - 3]
                break
    return newpath2 + "wav" + newpath1 + ".wav      " + newpath2 + "mfcc" + newpath1 + ".mfcc"

if len(sys.argv) >= 3:
    train_wav = sys.argv[1]
    test_wav = sys.argv[2]
    pTrain = open(train_wav,'r')
    pTest = open(test_wav,'r')
    pWrite = open("..\\pro\\getmfcc.scp",'w')
    for dir in (pTrain):
        if(isfile(dir)):
            pWrite.write(complement(dir) + '\n')

    pWrite.write("\n")

    for dir in (pTest):
       if(isfile(dir)):
            pWrite.write(complement(dir) + '\n')

else:
    print "[error]: parament must be two"

