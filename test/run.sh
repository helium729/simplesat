executable_path=../build/simplesat

for f in *.cnf
do
    echo "Running $f"
    base_file=`echo $f | sed 's/.cnf//'`
    result_file=`echo $f | sed 's/.cnf/.out/'`
    $executable_path $f $result_file
    python "check.py" $base_file
    rm $result_file
done
