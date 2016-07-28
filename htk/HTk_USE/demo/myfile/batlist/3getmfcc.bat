@echo off
cd .> ..\bate\train_wav.txt
cd .> ..\bate\test_wav.txt
dir /s /b ..\..\data\train\wav >> ..\bate\train_wav.txt
dir /s /b ..\..\data\test\wav  >> ..\bate\test_wav.txt
python 3getmfccSCP.py ..\bate\train_wav.txt ..\bate\test_wav.txt
HCopy -A -D -C ..\pro\analysis.conf -S ..\pro\getmfcc.scp
