#!/usr/bin/env bash

echo "----- Creating archive of your source ----"
cd coconut/
echo "Archiving CoCoNut..."
git archive --prefix="civicc/coconut/" -o coconut.tar HEAD . || exit 1
cd ../
echo "Archiving civicc..."
git archive --prefix="civicc/" -o civicc.tar HEAD . || exit 1
echo "Combining..."
tar --concatenate --file=civicc.tar coconut/coconut.tar || exit 1
echo "Compressing..."
gzip -9 civicc.tar
echo "----- Finished ------"
echo "Always double check the created archive!"
