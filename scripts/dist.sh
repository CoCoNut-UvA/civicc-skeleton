#!/usr/bin/env bash

if ! [[ -z $(git status --porcelain) ]]; then
    echo "git status is not clean. Ensure it is before making an archive."
    echo "---------------------------------------------------------------"
    git status
    exit 1
fi

echo "----- Creating archive of your source ----"
cd coconut/
echo "Archiving CoCoNut..."
git archive --prefix="civicc/coconut/" -o coconut.tar HEAD . || exit 1
cd ../
echo "Archiving civicc..."
git archive --prefix="civicc/" -o civicc.tar HEAD . || exit 1
echo "Combining..."
tar --concatenate --file=civicc.tar coconut/coconut.tar || exit 1
rm coconut/coconut.tar
echo "Compressing..."
gzip -9 civicc.tar
echo "----- Finished ------"
echo "Always double check the created archive!"
