import re
import sys
import subprocess

    
def predict(path, styles=["Forró", "Hip-hop", "MPB", "Rock"]):
    results = []

    for model in styles:
        model_path = f"models/{model}.bin"
        cmd = ["./a.out", path, "-p", "30", "-i", model_path]

        try:
            result = subprocess.run(cmd, capture_output = True, text = True)
            avgLen = re.search(r"Average length: (.+)b/symbol", result.stdout).group(1)
            results.append(float(avgLen))
            print(f"Execution successful for {model}!\tl={avgLen}")
        except subprocess.CalledProcessError:
            print(f"Execution failed for {model}!")

    return styles[results.index(min(results))]

if __name__ == "__main__":
    styles=["Forró", "Hip-hop", "MPB", "Rock"]
    path = sys.argv[1]
    pathStyle = path.split("/")[1]
    correctStyle = pathStyle if pathStyle in styles else None

    predictedStyle = predict(path)
    print(f"Prediction {'' if not correctStyle else '✅' if predictedStyle == correctStyle else '❌'}: {predictedStyle}")
