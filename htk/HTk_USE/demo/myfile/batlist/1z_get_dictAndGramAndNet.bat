@echo off
python get_dictAndGram.py ..\bate\wordlist.txt
if exist ..\..\net.slf (
	copy ..\..\net.slf ..\pro\net.slf
) else (
	Hparse -A -D -T 1 ..\pro\gram.txt ..\pro\net.slf
)
copy ..\bate\wordlist.txt ..\pro\hmmlist.txt