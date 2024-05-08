import subprocess
import os
import shutil
from sklearn.model_selection import train_test_split

songsPath = "./songs"
styles = {}

for dirpath, dnames, fnames in os.walk(songsPath):
    folders = dirpath.split('/')
    if(len(folders) == 4):
        for file in fnames:
            if(folders[2] in styles):
                styles[folders[2]].append(f"{dirpath}/{file}")
            else:
                styles[folders[2]] = [f"{dirpath}/{file}"]

dataSets = {key: train_test_split(styles[key], test_size=0.3, random_state=42) for key in styles}

for style in dataSets:
    for i, dataSet in enumerate(dataSets[style]):
        path = f"dataset/{style}/{'train' if i == 0 else 'test'}"
        os.makedirs(path, exist_ok=True)
        for music in dataSet:
            shutil.copy(music, path)
        subprocess.run(["tar", "-cf", f"{path}.tar", path])
