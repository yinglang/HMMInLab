@echo off
cd .> ..\bate\wordlist.txt
dir /b ..\..\data\train\wav >> ..\bate\wordlist.txt
echo sil >> ..\bate\wordlist.txt

cd .> ..\bate\test_wordlist.txt
dir /b ..\..\data\test\wav >> ..\bate\test_wordlist.txt

if exist ..\bate\hmmState.txt (
	python getWordState.py ..\bate\wordlist.txt has_exist
) else (
	python getWordState.py ..\bate\wordlist.txt not_exist
)
