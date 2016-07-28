@echo off
md ..\..\data\train\mfcc
md ..\..\data\test\mfcc
for /f %%i in (..\bate\wordlist.txt) do (
	if %%i == sil ( echo pass ) else (
		md ..\..\data\train\mfcc\%%i
	)
)

for /f %%i in (..\bate\test_wordlist.txt) do (
	md ..\..\data\test\mfcc\%%i
)
copy analysis.conf ..\pro\analysis.conf
