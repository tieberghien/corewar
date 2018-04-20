rm test_mine.txt test_theirs.txt

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
	echo $filename >> test_mine.txt
	hexdump -Cv $fullname 2> /dev/null >> test_mine.txt
	./asm_cp $elem
	filename=$(echo ${elem%.*})
	fullname="${filename}.cor"
	echo $filename >> test_theirs.txt
	hexdump -Cv $fullname 2> /dev/null >> test_theirs.txt
done

rm -rf $(find . -name "*.cor")
