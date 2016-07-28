@echo off
cd .> ..\pro\test_lablist.txt
cd .> ..\bate\test_wordlist.txt
dir /b ..\..\data\test\wav >> ..\bate\test_wordlist.txt
for /f %%i in (..\bate\test_wordlist.txt) do (
	cd .> ..\bate\everyTeslabtList.txt
	dir /b ..\..\data\test\lab\%%i >> ..\bate\everyTeslabtList.txt
	for /f %%j in (..\bate\everyTeslabtList.txt) do (
		echo ..\..\data\test\lab\%%i\%%j >> ..\pro\test_lablist.txt
	)
)

python getref.py ..\pro\test_lablist.txt
