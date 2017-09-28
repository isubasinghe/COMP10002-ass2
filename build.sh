
echo $"\n"
echo $"\n"
echo "Environment: `uname -a`"
echo "Compiler: `$CC --version`"
echo $"\n"
echo $"\n"
gcc ass2-soln.c -Wall -lm -o ass2
chmod +x ass2
./ass2 || exit 1
python diff_checker.py || exit 1