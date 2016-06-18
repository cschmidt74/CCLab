#!/bin/bash

failedFails=0;
totalFails=0;

for f in Testfiles/fails/*
do
  echo "Processing $f file...";
  cat $f;
  echo;
  if(! ./parser < $f == 0) then
  	((failedFails++))
  fi
  ((totalFails++))
  echo "__________________________________________";
  echo;
done

passedPasses=0;
totalPasses=0;

for f in Testfiles/passes/*
do
  echo "Processing $f file...";
  cat $f;
  echo;
  if(./parser < $f == 0) then
  	((passedPasses++))
  fi
  ((totalPasses++))
  echo "__________________________________________";
  echo;
done


echo $failedFails of $totalFails tests correctly failed
echo $passedPasses of $totalPasses tests correctly passed