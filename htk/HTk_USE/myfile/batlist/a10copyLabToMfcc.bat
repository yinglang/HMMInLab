@echo off
for /f %%i in (..\bate\test_wordlist.txt) do (
	cd . > ..\bate\everyTeslabtList.txt
	dir /b ..\..\data\test\lab\%%i >> ..\bate\everyTeslabtList.txt
	for /f %%j in (..\bate\everyTeslabtList.txt) do (
		copy ..\..\data\test\lab\%%i\%%j ..\..\data\test\mfcc\%%i\%%j
	)
)