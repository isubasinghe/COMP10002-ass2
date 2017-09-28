
echo ""
echo ""
echo "Environment: `uname -a`"
echo "Compiler: `$CC --version`"
echo ""
echo ""
gcc ass2-soln.c -Wall -lm -o ass2
chmod +x ass2
echo ""
echo ""
./ass2 || exit 1
echo ""
echo ""
python diff_checker.py || exit 1
