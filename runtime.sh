#!/bin/zsh

year=2024

print "Day:"
read  day

cd $year/$day

{multitime -n 10 -q ./build/part1} 2> ../../runtimes/temp1.txt
{multitime -n 10 -q ./build/part2} 2> ../../runtimes/temp2.txt

cd ../../runtimes

grep "user" temp1.txt > t1.txt
grep "user" temp2.txt > t2.txt

# mean, min, max 
awk  '{print $2 "\t" $4 "\t" $6}' t1.txt > temp1.txt
awk  '{print $2 "\t" $4 "\t" $6}' t2.txt > temp2.txt

p1_mean=$(cat temp1.txt | awk '{print $1}') 
p1_min=$(cat temp1.txt | awk '{print $2}') 
p1_max=$(cat temp1.txt | awk '{print $3}')

p2_mean=$(cat temp2.txt | awk '{print $1}') 
p2_min=$(cat temp2.txt | awk '{print $2}') 
p2_max=$(cat temp2.txt | awk '{print $3}')


echo "## $day
| Part | Fastest (s) | Slowest (s) | Average (s) |
| ---- | ------------ | ------------ | ------------ |
| Part 1 | $p1_min | $p1_max | $p1_mean |
| Part 2 | $p2_min | $p2_max | $p2_mean |

" > $day

rm temp1.txt temp2.txt t1.txt t2.txt

echo "#Execution Times:
" > ../$year/README.md

for file in ./*; do
	cat $file >> ../$year/README.md
done

