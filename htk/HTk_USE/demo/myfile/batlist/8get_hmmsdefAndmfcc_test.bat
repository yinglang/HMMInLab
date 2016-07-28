@echo off
python gethmmsdef.py ..\bate\wordlist.txt

echo make mfcc_test
python get_test_mfcc.py ..\..\data\test\mfcc ..\bate\test_wordlist.txt ..\\pro\\mfcc_test.txt