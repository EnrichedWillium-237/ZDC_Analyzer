#!/bin/bash

minBiasSet=HIMinimumBias2 ####change the minbias dataset you want

python ./das_client.py --query="run dataset=/$minBiasSet/HIRun2015-PromptReco-v1/AOD" --limit=0 > filelist.txt

while IFS='' read -r line || [[ -n "$line" ]]; do
  runNumber=$line
  crab status -d crab_PbPb2015_PromptReco_MinBias3_${runNumber}
  
done < "filelist.txt"

rm filelist.txt