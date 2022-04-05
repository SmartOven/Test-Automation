#!/bin/bash

touch input.txt
touch py_out.txt
touch cpp_out.txt

result="true"

while [ $result = "true" ]
  do
    # Generate test
    python3 test_generator.py > input.txt

    # Test on Python
    cat input.txt | python3 solution.py > py_out.txt

    # Test on C++
    cat input.txt | ./a.out > cpp_out.txt

    # Check if answers are the same
    str_py=$(cat py_out.txt)
    str_cpp=$(cat cpp_out.txt)

    # If they arent - stop the loop and echo the test
    if [ "$str_py" != "$str_cpp" ]; then
        echo "==============================="
        echo "CPP result: "
        echo "$str_cpp"
        echo "==============================="
        echo "Python result:"
        echo "$str_py"
        echo "==============================="
        echo ""
        result="false"
    fi
  done

cat input.txt

rm input.txt
rm py_out.txt
rm cpp_out.txt