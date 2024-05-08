#!/bin/bash

datasetPath="dataset"
styles=( "Forró" "Hip-hop" "MPB" "Rock" )

# Output directory for storing resulting models
output_dir="predictions"
mkdir -p "$output_dir"

for model in "${styles[@]}"; do
    model_path="models/${model}.bin"
    for testStyle in "${styles[@]}"; do
        path="${datasetPath}/${testStyle}/test.tar"
        output_path="${output_dir}/${model}_${testStyle}.lzw"

        cmd="./a.out $path -c 30 -i $model_path -o $output_path"

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

echo "Test completed."

