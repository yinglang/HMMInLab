@echo off 
HRest -A -D -T 1 -S ..\..\training\mfcc_brightness.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_brightness.hmm -l brightness -L ..\..\data\train\lab\brightness brightness 
HRest -A -D -T 1 -S ..\..\training\mfcc_channel.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_channel.hmm -l channel -L ..\..\data\train\lab\channel channel 
HRest -A -D -T 1 -S ..\..\training\mfcc_color.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_color.hmm -l color -L ..\..\data\train\lab\color color 
HRest -A -D -T 1 -S ..\..\training\mfcc_sil.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_sil.hmm -l sil -L ..\..\data\train\lab\sil sil 
