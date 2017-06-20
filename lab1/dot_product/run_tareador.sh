USAGE="\n USAGE: ./run_tareador.sh prog \n
        prog        -> Tareador program name\n"

if (test $# -lt 1 || test $# -gt 1)
then
        echo -e $USAGE
        exit 0
fi

make $1

rm -rf .tareador_precomputed_*
tareador_gui.py --llvm --lite $1
