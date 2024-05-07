#!/bin/bash

datasetPath="dataset"
styles=( "Forró" "Hip-hop" "MPB" "Rock" )

# Output directory for storing resulting models
output_dir="models"
mkdir -p "$output_dir"

for style in "${styles[@]}"; do
    output_path="${output_dir}/${style}.bin"
    path="${datasetPath}/${style}/train.tar"

    cmd="./a.out $path -c 30 -e $output_path"

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

echo "Training completed."

