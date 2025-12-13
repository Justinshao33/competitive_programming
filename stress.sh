#!/usr/bin/env bash
g++ -std=c++20 $1.cpp -o $1
g++ -std=c++20 $2.cpp -o $2
g++ -std=c++20 $3.cpp -o $3

for i in {1..1000} ; do
    ./$3 > input.txt
    # st=$(date +%s%N)
    
    ./$1 < input.txt > output1.txt
    
    # echo "$((($(date +%s%N) - $st)/1000000))ms"
    
    ./$2 < output1.txt > output2.txt
    
    output2_content=$(cat output2.txt)
    if [ "$output2_content" == "-1" ]; then
        continue
    fi

    if cmp --silent -- "input.txt" "output2.txt" ; then
        continue
    fi
    
    echo Input:
    cat input.txt
    echo Your Output:
    cat output1.txt
    echo check Output:
    cat output2.txt
    exit 1
done
echo OK!