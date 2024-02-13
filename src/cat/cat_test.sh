gcc -Wall -Werror -Wextra cat.c -o test/s21_cat
cd test/
test_number=0
test_count=10
failed_count=0
files_list="text1 text2 text3 text4 text5"
options=(-s -e -n -v -b -t)

while [ $test_count!=0 ]; do
  test_count=$((test_count-1))
  for opt in ${options[@]}
  do
    echo -e "TEST NUMBER |$test_number|"
    ./s21_cat $opt $files_list > s21_res
    cat $opt $files_list > cat_res
    echo -e "$(diff -s cat_res s21_res)\n"
    if [[ $(diff -q cat_res s21_res) ]]
    then
      echo "---------------------------------------------------"
      echo -e "\nFAIL: test failed at $opt\n"
      failed_count=$((failed_count + 1))
    fi
    test_number=$((test_number + 1))
  done
done

cd ..

echo "-----------------------RESULT-------------------------"
if [ $failed_count == 0 ]
	then
		echo -e "\nSUCCESS\n"
	else
		echo -e "\nFAIL COUNT: $failed_count\n"
fi