@echo off
cd . > ..\bate\silLabdir.txt
dir /b ..\..\data\train\lab >> ..\bate\silLabdir.txt
md ..\..\data\train\lab\sil
for /f %%i in (..\bate\silLabdir.txt) do (
	cd . > ..\bate\everyLabList.txt
	dir /b ..\..\\data\train\lab\%%i >> ..\bate\everyLabList.txt
	for /f %%j in (..\bate\everyLabList.txt) do (
		copy ..\..\data\train\lab\%%i\%%j ..\..\data\train\lab\sil\%%j
	)
)
