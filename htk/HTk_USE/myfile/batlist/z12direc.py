# coding=utf-8
import os
import sys
if len(sys.argv) == 2 :
    if sys.argv[1] == "1":
        ##判断训练wav，lab测试wav,lab是否存在
        rootDir1 = "..\\..\\data\\train\\wav"
        rootDir2 = "..\\..\\data\\train\\lab"
        rootDir3 = "..\\..\\data\\test\\wav"
        rootDir4 = "..\\..\\data\\test\\lab"

        if len(os.listdir(rootDir1)) == 0 or len(os.listdir(rootDir2)) == 0 or \
                        len(os.listdir(rootDir3)) == 0 or len(os.listdir(rootDir4)) == 0:
            print "please put train wav into \\data\\train\\wav\\ ,like \\data\\train\\wav\\caozuo\\caozuo1.wav"
            print "please put train lab into \\data\\train\\lab\\ ,like \\data\\train\\lab\\caozuo\\caozuo1.lab"
            print "please put test wav into \\data\\test\\wav\\ ,like \\data\\test\\wav\\caozuo\\caozuo2.wav"
            print "please put test lab into \\data\\test\\lab\\ ,like \\data\\test\\lab\\caozuo\\caozuo2.lab"
            raw_input()

        while len(os.listdir(rootDir1)) == 0:
            print "[ERROR] please put train wav data into \\data\\train\\wav\\"
            raw_input("press any key to continue afte solved this problem")

        while len(os.listdir(rootDir2)) == 0:
            print "[ERROR] please put train lab file into \\data\\train\\lab\\"
            raw_input("press any key to continue afte solved this problem")

        justTrain = 0
        while len(os.listdir(rootDir3)) == 0 and (not justTrain):
            a = raw_input("if you just want to train to get HMM,not use test press 'Y' or 'y', if not press 'N' or 'n'")
            if a == 'Y' or a == 'y':
                justTrain = 1
            else:
                print "[ERROR] please put test wav data into \\data\\test\\wav\\"
                raw_input("press any key to continue afte solved this problem")

        while len(os.listdir(rootDir4)) == 0 and (not justTrain):
            print "[ERROR] please put test lab file into \\data\\test\\lab\\"
            raw_input("press any key to continue afte solved this problem")

