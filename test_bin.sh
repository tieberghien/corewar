rm test_mine_binary.txt test_theirs_binary.txt

i="0"

for file in $(find . -name "*.s")
do
	src[$i]=$file
	let "i = i + 1"
done

for elem in ${src[@]}
do
	echo "\n"
	echo $elem
	./asm $elem
	filename=$(echo ${elem%.*})
	fullname="${filename}.cor"
	echo $filename >> test_mine_binary.txt
	cat $fullname 2> /dev/null >> test_mine_binary.txt
	./asm_cp $elem
	filename=$(echo ${elem%.*})
	fullname="${filename}.cor"
	echo $filename >> test_theirs_binary.txt
	cat $fullname 2> /dev/null >> test_theirs_binary.txt
done

rm -rf $(find . -name "*.cor")
