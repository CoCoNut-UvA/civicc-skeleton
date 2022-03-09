#!/usr/bin/env bash
CIVAS=${CIVAS-../bin/civas}
CIVVM=${CIVVM-../bin/civvm}
CIVCC=${CIVCC-../bin/civcc}
CFLAGS=${CFLAGS-}
RUN_FUNCTIONAL=${RUN_FUNCTIONAL-1}

ALIGN=52

total_tests=0
failed_tests=0

function echo_success {
    echo -e '\E[27;32m'"\033[1mok\033[0m"
}

function echo_failed {
    echo -e '\E[27;31m'"\033[1mfailed\033[0m"
}

# The real tests: compile a file, run it, and compare the output to the
# expected output.
function check_output {
    file=$1
    expect_file=${file%.*}.out

    if [ ! -f $file ]; then return; fi

    total_tests=$((total_tests+1))
    printf "%-${ALIGN}s " $file:

    if $CIVCC $CGLAGS -o tmp.s $file > tmp.out 2>&1 &&
       $CIVAS tmp.s -o tmp.o > tmp.out 2>&1 &&
       $CIVVM tmp.o > tmp.out 2>&1 &&
       mv tmp.out tmp.res &&
       diff tmp.res $expect_file --side-by-side --ignore-space-change > tmp.out 2>&1
    then
        echo_success
    else
        echo_failed
        echo -------------------------------
        cat tmp.out
        echo -------------------------------
        echo
        failed_tests=$((failed_tests+1))
    fi

    rm -f tmp.res tmp.s tmp.o tmp.out
}

# Special case: multiple files must be compiled and run together (e.g., for
# extern variables). Compile all the *.cvc files in the given directory, run
# them, and compare the output to the content of expected.out.
function check_combined {
    dir=$1
    expect_file=$dir/expected.out

    if [ ! -d $dir ]; then return; fi
    if [ ! -f $expect_file ]; then return; fi

    files=`find $dir -maxdepth 1 -name \*.cvc`
    total_tests=$((total_tests+1))
    compiled=1
    ofiles=""
    compiled_files=""

    printf "%-${ALIGN}s " $dir:

    for file in $files
    do
        asfile=${file%.*}.s
        ofile=${file%.*}.o
        ofiles="$ofiles $ofile"

        if $CIVCC $CGLAGS -o $asfile $file > /dev/null 2>&1 &&
           $CIVAS -o $ofile $asfile 2>&1
        then
            compiled_files="$compiled_files `basename $file`"
        else
            compiled=0
        fi
    done

    if [ $compiled -eq 1 ]
    then
        if $CIVVM $ofiles > tmp.out 2>&1 &&
           mv tmp.out tmp.res &&
           diff tmp.res $expect_file --side-by-side --ignore-space-change > tmp.out 2>&1
        then
            echo_success
        else
            echo_failed
            echo -------------------------------
            cat tmp.out
            echo -------------------------------
            echo
            failed_tests=$((failed_tests+1))
        fi
    else
        echo "failed, only compiled$compiled_files"
        failed_tests=$((failed_tests+1))
    fi

    rm -f $d/*.s $d/*.o tmp.out tmp.res
}

# Easy tests, check if the parser, context analysis and typechecking work
# properly by checking if the compiler returns 0 (or non-zero when expected to
# fail)
function check_return {
    file=$1
    expect_failure=$2

    if [ ! -f $file ]; then return; fi

    total_tests=$((total_tests+1))
    printf "%-${ALIGN}s " $file:

    if $CIVCC $CFLAGS $file -o tmp.s > tmp.out 2>&1
    then
        if [ $expect_failure -eq 1 ]; then
            echo_failed
            failed_tests=$((failed_tests+1))
        else
            echo_success
        fi
    else
        if [ $expect_failure -eq 1 ]; then
            echo_success
        else
            echo_failed
            echo -------------------------------
            cat tmp.out
            echo -------------------------------
            echo
            failed_tests=$((failed_tests+1))
        fi
    fi

    rm -f tmp.s tmp.out
}

function run_dir {
    BASE=$1

    for f in $BASE/check_success/*.cvc; do
        check_return $f 0
    done

    for f in $BASE/check_error/*.cvc; do
        check_return $f 1
    done

    if [ $RUN_FUNCTIONAL -eq 1 ]; then
        for f in $BASE/functional/*.cvc; do
            check_output $f
        done

        for d in $BASE/combined_*; do
            check_combined $d
        done
    fi

    echo
}

CIVCC=$1
shift 1
for arg in $@; do
    run_dir $arg
done

echo $total_tests tests, $failed_tests failures
test $failed_tests -eq 0 || exit 1
