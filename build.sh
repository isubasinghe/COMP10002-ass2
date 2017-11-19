
echo ""
echo ""
echo "Environment: `uname -a`"
echo "Compiler: `$CC --version`"
echo ""
echo ""
gcc ass2-soln.c -Wall -lm -o ass2 -O3
chmod +x ass2
echo ""
echo ""
./ass2 < ./test_cases/test0.txt|| exit 1
echo ""
echo ""
./ass2 < ./test_cases/test1.txt|| exit 1
echo ""
echo ""
./ass2 < ./test_cases/test2.txt|| exit 1
echo ""
echo ""

