#!/bin/bash

# Test Caesar cipher
printf "\t\t\t\t\n\nTESTING CAESAR\n\n"
printf "Caesar Encryption: Key 3\nThis is input: "
cat input
./cipher CES 3 ENC input output
printf "Output is: "
cat output
printf "\nCaesar Decryption: Key 3\nThis is input: "
cat output
./cipher CES 3 DEC output outputDec
printf "Output is: "
cat outputDec
printf "Should be: "
cat input

# Test Row Transposition cipher
printf "\t\t\t\t\n\nTESTING ROW TRANSPOSITION\n\n"
printf "\nRow Transposition Encryption: Key 312\nThis is input: "
cat input
./cipher RTS 312 ENC input output
printf "Output is: "
cat output
printf "\nRow Transposition Decryption: Key 312\nThis is input: "
cat output
./cipher RTS 312 DEC output outputDec
printf "Output is: "
cat outputDec
printf "Should be similar: "
cat input

# Test Vigenere cipher
printf "\t\t\t\t\n\nTESTING VIGENERE\n\n"
printf "\nVigenere Encryption: Key security\nThis is input: "
cat input
./cipher VIG security ENC input output
printf "Output is: "
cat output
printf "\nVigenere Decryption: Key security\nThis is input: "
cat output
./cipher VIG security DEC output outputDec
printf "Output is: "
cat outputDec
printf "Should be similar: "
cat input

# Test Railfence cipher
printf "\t\t\t\t\n\nTESTING RAILFENCE\n\n"
printf "\nRailfence Encryption: Key 3\nThis is input: "
cat input
./cipher RFC 3 ENC input output
printf "Output is: "
cat output
printf "\nRailfence Decryption: Key 3\nThis is input: "
cat output
./cipher RFC 3 DEC output outputDec
printf "Output is: "
cat outputDec
printf "Should be similar: "
cat input

# Test Playfair cipher
printf "\t\t\t\t\n\nTESTING PLAYFAIR\n\n"
printf "\nPlayfair Encryption: Key security\nThis is input: "
cat input
./cipher PLF security ENC input output
printf "Output is: "
cat output
printf "\nPlayfair Decryption: Key security\nThis is input: "
cat output
./cipher PLF security DEC output outputDec
printf "Output is: "
cat outputDec
printf "Should be similar: "
cat input
