gcc -Wall -Werror -Wextra cat.c -o test/s21_cat
cd test

SUCCESS=0
FAILED=0
TEST_COUNT=1
DIFF_RES=0
FLAGS=(-b -e -n -s -t -v)
FILES=(TEST_FILE_1 TEST_FILE_2 TEST_FILE_3 TEST_FILE_4 TEST_FILE_5)
for flag in ${FLAGS[@]}
do
  for file in ${FILES[@]}
  do
    ./s21_cat $flag $file > s21_cat_res
    cat $flag $file > cat_res
    DIFF_RES="$(diff -s s21_cat_res cat_res)"
    if [ "$DIFF_RES" == "Files s21_cat_res and cat_res are identical" ]
    then
      SUCCESS=$((SUCCESS + 1))
      echo "TEST $TEST_COUNT ------------ $flag RESULT: -----SUCCESS-----"
    else
      FAILED=$((FAILED + 1))
      echo "TEST $TEST_COUNT ------------ $falg RESULT: -----FAILED------"
    fi
    TEST_COUNT=$((TEST_COUNT + 1))
  done
done

declare -a SPECIAL_TESTS=(
  "-b -e -n -s -t -v TEST_FILE_2"
  "-benstv TEST_FILE_3"
  "-n -b TEST_FILE_3"
  "-n -b -e TEST_FILE_3"
  "-n -b -t -e TEST_FILE_3"
  "-b -v -n -s TEST_FILE_3"
)

for i in "${SPECIAL_TESTS[@]}"
do
  ./s21_cat $i > s21_cat_res
  cat $i > cat_res
  DIFF_RES="$(diff -s s21_cat_res cat_res)"
  if [ "$DIFF_RES" == "Files s21_cat_res and cat_res are identical" ]
  then
    SUCCESS=$((SUCCESS + 1))
    echo "TEST $TEST_COUNT ------------ RESULT: -----SUCCESS----- $i"
  else
    FAILED=$((FAILED + 1))
    echo "TEST $TEST_COUNT ------------ RESULT: -----FAILED----- $i"
  fi
  TEST_COUNT=$((TEST_COUNT + 1))
done


if [ $FAILED == 0 ]
then
  echo "-----------TOTAL RESULT: SUCCESS!!-----------"
else
  echo "-----------TOTAL RESULT: FAILED $FAILED!!-----------"
fi

cd ..