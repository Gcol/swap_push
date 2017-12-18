iteration=0
fin=1000
instrucion=0
median=0

while test $iteration != $fin
    do
    ARG=`ruby -e "puts (-250..250).to_a.reverse.join(' ')"`
    ./push_swap/push_swap $ARG > test.txt
    instrucion=$(bc <<< "$instrucion + $(wc -l test.txt | awk '{print $1}')")
    iteration=$(($iteration + 1))
done
    median=$(bc <<< "$instrucion/1000")
    echo "Nb instruction moyenne = "$median
    rm -rf test.txt
