gcc -Wall -Werror -Wextra cat.c -o test/s21_cat
cd test
number=1
count=100
failed_count=0
files="additional_file1 additional_file2 all_characters empty_file empty_lines_file"
flags=(-s -e -n -v -b -t)

while [ $count!=0 ]; do
  count=$((count -1))
  for flag in ${flags[@]}
  do
    echo -e "TEST NUMBER |$number|"
    ./s21_cat $flag $files > s21_res
    cat $flag $files > cat_res
    echo -e "$(diff -s cat_res s21_res)\n"
    if [[ $(diff -q cat_res s21_res) ]]
    then
      echo "---------------------------------------------------"
      echo -e "\nFAIL: test failed at $flag\n"
      failed_count=$((failed_count + 1))
    fi
    number=$((number + 1))
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