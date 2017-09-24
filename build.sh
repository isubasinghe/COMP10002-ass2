

echo "Environment: `uname -a`"
echo "Compiler: `$CC --version`"
gcc -coverage ass2-soln.c -Wall -lm -o ass2
gcov ass2-soln.c
chmod +x ass2
./ass2 || exit 1
python diff_checker.py || exit 1