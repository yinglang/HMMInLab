@echo off 
HInit -A -D -T 1 -S ..\..\training\mfcc_caozuo.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_caozuo.hmm -l caozuo -L ..\..\data\train\lab\caozuo caozuo 
HInit -A -D -T 1 -S ..\..\training\mfcc_changge.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_changge.hmm -l changge -L ..\..\data\train\lab\changge changge 
HInit -A -D -T 1 -S ..\..\training\mfcc_sil.txt -M ..\..\model\hmm0 -H ..\..\model\proto\hmm_sil.hmm -l sil -L ..\..\data\train\lab\sil sil 
