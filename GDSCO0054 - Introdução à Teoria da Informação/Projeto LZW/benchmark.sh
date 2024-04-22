#!/bin/bash

paths=( "silesia/dickens" "silesia.tar"  )
modes=('c' 'd')
strategies=(1 2 3)
sizes=(12 15 18 21)

# Output directory for storing results
output_dir="benchmark"
mkdir -p "$output_dir"

for path in "${paths[@]}"; do
    # Extract file name for output naming
    filename=$(basename "$path")

    for mode in "${modes[@]}"; do
        for strategy in "${strategies[@]}"; do
            for size in "${sizes[@]}"; do
                output_path="$output_dir/${filename}_${mode}_${size}"

                if [[ "$mode" == "c" ]]; then
                    cmd="./a.out $path -c $size -s $strategy -o $output_path.lzw"
                else
                    cmd="./a.out $path -d $size -s $strategy -o $output_path.out"
                fi

                printf "Executing command: $cmd\n"

                 # Start the timer and execute the command
                t0=$(date +%s.%N)
                eval "$cmd"
                t1=$(date +%s.%N)

                delta=$(echo "$t1 - $t0" | bc)

                # Check the result of the command
                if [ $? -eq 0 ]; then
                    printf "Execution successful for $cmd!\n"
                    printf "Elapsed time: $delta seconds\n\n\n"
                else
                    printf "Execution failed for $cmd!\n"
                    printf "Elapsed time: $delta seconds\n\n\n"
                fi
            done
        done
    done
done

echo "Benchmark completed."

