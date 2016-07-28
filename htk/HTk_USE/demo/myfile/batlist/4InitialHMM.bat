@echo off
md ..\..\model
md ..\..\model\proto
for %%i in (0,1,2,3) do (
	md ..\..\model\hmm%%i
	)
python setHMMFile.py ..\bate\hmmState.txt
