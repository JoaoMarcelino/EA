set -e
echo "compiling..."
g++ -std=c++17 -Wall -Wextra -O2 "$1.cpp" -lm

echo "running..."
./a.out <test.in >test.out