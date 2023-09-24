#!/bin/bash

#TEST NO FLAGS

./s21_cat s21_cat.c > s21_cat.txt
cat s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt
 
#TEST FLAGS SOLO

./s21_cat -b s21_cat.c > s21_cat.txt
cat -b s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -e s21_cat.c > s21_cat.txt
cat -e s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -n s21_cat.c > s21_cat.txt
cat -n s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -s s21_cat.c > s21_cat.txt
cat -s s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt
 
./s21_cat -t s21_cat.c > s21_cat.txt
cat -t s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

# ./s21_cat -e symbols.txt > s21_cat.txt
# cat -e symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
#  
# ./s21_cat -et symbols.txt > s21_cat.txt
# cat -et symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
#  
# ./s21_cat -te symbols.txt > s21_cat.txt
# cat -te symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
# 
# ./s21_cat -ve symbols.txt > s21_cat.txt
# cat -ve symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
# 
# ./s21_cat -tv symbols.txt > s21_cat.txt
# cat -tv symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
# 
# ./s21_cat -t symbols.txt > s21_cat.txt
# cat -t symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
# 
# ./s21_cat -b symbols.txt > s21_cat.txt
# cat -b symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
#  
# ./s21_cat -vet symbols.txt > s21_cat.txt
# cat -e symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
# 
# ./s21_cat -tev symbols.txt > s21_cat.txt
# cat -e symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
# 
# ./s21_cat -etv symbols.txt > s21_cat.txt
# cat -e symbols.txt > cat.txt
# diff -n s21_cat.txt cat.txt <&2
# rm s21_cat.txt cat.txt
# TEST FLAGS DOUBLE

./s21_cat -be s21_cat.c > s21_cat.txt
cat -be s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bn s21_cat.c > s21_cat.txt
cat -bn s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bs s21_cat.c > s21_cat.txt
cat -bs s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bt s21_cat.c > s21_cat.txt
cat -bt s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -ne s21_cat.c > s21_cat.txt
cat -ne s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -ns s21_cat.c > s21_cat.txt
cat -ns s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -nt s21_cat.c > s21_cat.txt
cat -nt s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -es s21_cat.c > s21_cat.txt
cat -es s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -et s21_cat.c > s21_cat.txt
cat -et s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -st s21_cat.c > s21_cat.txt
cat -st s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

# TEST FLAGS TRIPLE

./s21_cat -bet s21_cat.c > s21_cat.txt
cat -bet s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bes s21_cat.c > s21_cat.txt
cat -bes s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -ben s21_cat.c > s21_cat.txt
cat -ben s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bns s21_cat.c > s21_cat.txt
cat -bns s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bnt s21_cat.c > s21_cat.txt
cat -bnt s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bst s21_cat.c > s21_cat.txt
cat -bst s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -nes s21_cat.c > s21_cat.txt
cat -nes s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -nst s21_cat.c > s21_cat.txt
cat -nst s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -net s21_cat.c > s21_cat.txt
cat -net s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -est s21_cat.c > s21_cat.txt
cat -est s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

# TEST FLAGS MIXED

./s21_cat -nest s21_cat.c > s21_cat.txt
cat -nest s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -best s21_cat.c > s21_cat.txt
cat -best s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bent s21_cat.c > s21_cat.txt
cat -bent s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bens s21_cat.c > s21_cat.txt
cat -bens s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt

./s21_cat -bnst s21_cat.c > s21_cat.txt
cat -bnst s21_cat.c > cat.txt
diff -n s21_cat.txt cat.txt <&2
rm s21_cat.txt cat.txt
