

echo "Environment: `uname -a`"
echo "Compiler: `$CC --version`"
gcc ass2-soln.c -Wall -lm -o ass2
chmod +x ass2
./ass2