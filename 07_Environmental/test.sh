#!/bin/bash

echo "Testing MD5 with file..."
echo -n "hello" > test_file.txt

result=$(echo 'MD5 test_file.txt' | ./rhasher 2>/dev/null | grep -oE '[0-9a-f]{32}')
expected=$(md5sum test_file.txt | awk '{print $1}')

if [ "$result" != "$expected" ]; then
    echo "MD5 file test failed!"
    echo "Expected: $expected"
    echo "Got: '$result'"
    rm -f test_file.txt
    exit 1
fi
echo "MD5 file test passed"

echo "Testing SHA1 with file..."
result=$(echo 'SHA1 test_file.txt' | ./rhasher 2>/dev/null | grep -oE '[0-9a-f]{40}')
expected=$(sha1sum test_file.txt | awk '{print $1}')

if [ "$result" != "$expected" ]; then
    echo "SHA1 file test failed!"
    echo "Expected: $expected"
    echo "Got: '$result'"
    rm -f test_file.txt
    exit 1
fi
echo "SHA1 file test passed"

rm -f test_file.txt
echo "All tests passed!"
exit 0
