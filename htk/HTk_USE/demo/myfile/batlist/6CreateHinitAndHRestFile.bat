@echo off
cd .> 6HinitFile.bat
cd .> 6HRest1File.bat
cd .> 6HRest2File.bat
cd .> 6HRest3File.bat
echo @echo off >> 6HinitFile.bat
echo @echo off >> 6HRest1File.bat
echo @echo off >> 6HRest2File.bat
echo @echo off >> 6HRest3File.bat
for /f %%i in (../bate/wordlist.txt) do (
	echo HInit -A -D -T 1 -S ..\..\training\mfcc_%%i.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_%%i.hmm -l %%i -L ..\..\data\train\lab\%%i %%i >> 6HinitFile.bat
	echo HRest -A -D -T 1 -S ..\..\training\mfcc_%%i.txt -M ..\..\model\hmm1 -H ..\..\model\hmm0\hmm_%%i.hmm -l %%i -L ..\..\data\train\lab\%%i %%i >> 6HRest1File.bat
	echo HRest -A -D -T 1 -S ..\..\training\mfcc_%%i.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_%%i.hmm -l %%i -L ..\..\data\train\lab\%%i %%i >> 6HRest2File.bat
	echo HRest -A -D -T 1 -S ..\..\training\mfcc_%%i.txt -M ..\..\model\hmm3 -H ..\..\model\hmm2\hmm_%%i.hmm -l %%i -L ..\..\data\train\lab\%%i %%i >> 6HRest3File.bat
)

