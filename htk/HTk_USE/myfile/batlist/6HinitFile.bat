@echo off 
HInit -A -D -T 1 -S ..\..\training\mfcc_brightness.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_brightness.hmm -l brightness -L ..\..\data\train\lab\brightness brightness 
HInit -A -D -T 1 -S ..\..\training\mfcc_channel.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_channel.hmm -l channel -L ..\..\data\train\lab\channel channel 
HInit -A -D -T 1 -S ..\..\training\mfcc_color.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_color.hmm -l color -L ..\..\data\train\lab\color color 
HInit -A -D -T 1 -S ..\..\training\mfcc_sil.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_sil.hmm -l sil -L ..\..\data\train\lab\sil sil 
