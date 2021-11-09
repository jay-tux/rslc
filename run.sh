#!/usr/bin/zsh

echo ' -- Building RSLC ... -- '
make rslc
if [ $? -eq 0 ]; then
  echo ' -- Build Succeeded -- '
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./bin/
  echo ' -- Running Compiler -- '
  bin/rslc $@
  if [ $? -ne 0 ]; then
    echo ' -- RSLC error -- '
  else
    echo ' -- Compilation Finished -- '
  fi
else
  echo ' -- Building RSLC failed -- '
fi
