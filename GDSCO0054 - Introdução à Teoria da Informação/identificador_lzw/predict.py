import re
import sys
import subprocess
# from datetime import datetime

dataset_path = "dataset"
styles = ["Forró", "Hip-hop", "MPB", "Rock"]
results = []

path = sys.argv[1]
pathStyle = path.split("/")[1]
correctStyle = pathStyle if pathStyle in styles else None

for model in styles:
    model_path = f"models/{model}.bin"
    cmd = ["./a.out", path, "-p", "30", "-i", model_path]

    try:
        result = subprocess.run(cmd, capture_output = True, text = True)
        avglen = re.search(r"Average length: (.+)b/symbol", result.stdout).group(1)
        results.append(float(avglen))
        print(f"Execution successful for {model}!")
    except subprocess.CalledProcessError:
        print(f"Execution failed for {model}!")

predictedStyle = styles[results.index(min(results))]
print(f"{'' if not correctStyle else '✔️ ' if predictedStyle == correctStyle else '✖️ '}prediction: {predictedStyle}")
