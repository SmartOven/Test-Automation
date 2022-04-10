#!/bin/bash

touch testcase.txt
touch my_out.txt
touch right_out.txt

result="true"

# Build solutions if needed
g++ -o my.out soluition.cpp
g++ -o right.out right_soluition.cpp

while [ $result = "true" ]
  do
    # Generate test
    python3 test_generator.py > testcase.txt

    # Test on right solution
    cat testcase.txt | ./right.out > right_out.txt

    # Test on my solution
    cat testcase.txt | ./my.out > my_out.txt

    # Check if answers are the same
    str_right=$(cat right_out.txt)
    str_my=$(cat my_out.txt)

    # If they arent - stop the loop and echo the test
    if [ "$str_right" != "$str_my" ]; then
        echo "==============================="
        echo "My result: "
        echo "$str_my"
        echo "==============================="
        echo "Right result:"
        echo "$str_right"
        echo "==============================="
        echo ""
        result="false"
    fi
  done

echo ""
echo "Test:"
cat testcase.txt

rm testcase.txt
rm my_out.txt
rm right_out.txt