@echo off
md ..\..\training
cd .> ..\bate\training_mfcc.txt
cd .> ..\..\training\mfcc_sil.txt
for /f %%i in (..\bate\wordlist.txt) do (
	if %%i == sil (
			echo sil pass
	) else (
		cd . > ..\bate\everyTrainMfccList.txt
		dir /b ..\..\data\train\mfcc\%%i >> ..\bate\everyTrainMfccList.txt
		cd . > ..\..\training\mfcc_%%i.txt
		for /f %%j in (..\bate\everyTrainMfccList.txt) do (
			echo ..\..\data\train\mfcc\%%i\%%j >> ..\..\training\mfcc_%%i.txt
			echo ..\..\data\train\mfcc\%%i\%%j >> ..\..\training\mfcc_sil.txt
		)
	)
	echo ..\..\training\mfcc_%%i.txt >> ..\bate\training_mfcc.txt
)
echo ..\..\training\mfcc_sil.txt >> ..\bate\training_mfcc.txt
