#!/bin/bash
g++ ./Source/lab5.cpp ./Source/avl.cpp -o lab5
echo 'Test 1'
echo 'Input commands: '
cat ./Tests/test1
echo 'Inpet tree: '
cat ./Tests/test1.txt
echo ''
./lab5 < ./Tests/test1

echo 'Test 2'
echo 'Input commands: '
cat ./Tests/test2
echo 'Inpet tree: '
cat ./Tests/test2.txt
echo ''
./lab5 < ./Tests/test2

echo 'Test 3'
echo 'Input commands: '
cat ./Tests/test3
echo 'Inpet tree: '
cat ./Tests/test3.txt
echo ''
./lab5 < ./Tests/test3

echo 'Test 4'
echo 'Input commands: '
cat ./Tests/test4
echo 'Inpet tree: '
cat ./Tests/test4.txt
echo ''
./lab5 < ./Tests/test4

echo 'Test 5'
echo 'Input commands: '
cat ./Tests/test5
echo 'Inpet tree: '
echo 'There is no input tree!'
echo ''
./lab5 < ./Tests/test5
