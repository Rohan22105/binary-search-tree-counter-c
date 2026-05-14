# Usage:    sh runtest.sh "list of numbers"
# Example:  sh runtest.sh "314 76 95064"

# Check that one command-line argument is given.
if [ "$1" = "" ]
then
    echo 'Usage:    sh runtest.sh LIST OF NUMBERS'
    echo 'Example:  sh runtest.sh 314 76 95064'
    echo 'Usage:    sh runtest.sh -d LIST OF NUMBERS'
    echo 'Example:  sh runtest.sh -d 314 76 95064'
else
    # Automatically determine which binaries to run.
    KERNEL=`uname -r | sed -e 's/.*-//'`
    MACHINE=`uname -m`

    if [ $KERNEL = 'azure' ]
    then
        EXEC='../../resources/asgn4/unique_hub'
    else
        if [ $MACHINE = 'aarch64' ]
        then
            EXEC='../../resources/asgn4/unique_arm'
        else
            EXEC='../../resources/asgn4/unique_x86'
        fi
    fi

    # Confirm that the executable file is where we expect it to be.
    if ! [ -f $EXEC ]
    then
        echo "Can't find reference program $EXEC"
    else
        # Run the executables.
        $EXEC $@ > expected.txt
        ./unique $@ > got.txt

        # Print any difference.
        # The diff -s option reports when the files are identical.
        diff -s expected.txt got.txt
    fi
fi

