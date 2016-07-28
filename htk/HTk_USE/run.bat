@echo off
cd myfile\batlist
cmd /c 0mdpredir.bat
python z12direc.py 1
cmd /c 1get_wordlistAndgetHMMState.bat
cmd /c 1z_get_dictAndGramAndNet
cmd /c 2md_mfccDirAndCopyConf.bat
cmd /c 3getmfcc.bat
cmd /c 4InitialHMM.bat
cmd /c 5trainingMfccList.bat
cmd /c 6CreateHinitAndHRestFile.bat
cmd /c 6Create_Sillab.bat
cmd /c 6HinitFile.bat
cmd /c 6HRest1File.bat
cmd /c 6HRest2File.bat
cmd /c 6HRest3File.bat
cmd /c 8get_hmmsdefAndmfcc_test.bat
cmd /c 9HVite.bat
cmd /c a10copyLabToMfcc.bat
cmd /c a10get_refAndLablist.bat
cmd /c a11HResults.bat