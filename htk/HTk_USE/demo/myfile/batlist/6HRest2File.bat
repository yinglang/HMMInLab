@echo off 
HRest -A -D -T 1 -S ..\..\training\mfcc_caozuo.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_caozuo.hmm -l caozuo -L ..\..\data\train\lab\caozuo caozuo 
HRest -A -D -T 1 -S ..\..\training\mfcc_changge.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_changge.hmm -l changge -L ..\..\data\train\lab\changge changge 
HRest -A -D -T 1 -S ..\..\training\mfcc_sil.txt -M ..\..\model\hmm2 -H ..\..\model\hmm1\hmm_sil.hmm -l sil -L ..\..\data\train\lab\sil sil 
