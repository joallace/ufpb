from bs4 import BeautifulSoup
import aiohttp
import asyncio
import json
import os

DISCOGRAPHIES_PATH = "discographies.json"
VAGALUME_URL = "https://www.vagalume.com.br"
DATA_PATH = "songs"

with open(DISCOGRAPHIES_PATH, 'r') as file:
    musicList = json.load(file)

async def get(path, artistUrl, music, session):
    musicPath = f'{path}/{music}.txt'

    if not os.path.isfile(musicPath):
        try:
            async with session.get(url=f'{VAGALUME_URL}/{artistUrl}/{music}.html') as r:
                soup = BeautifulSoup(await r.text(), "lxml")
                lyrics = soup.find('div', {'id': 'lyrics'})

                for br in lyrics.find_all("br"):
                    br.replace_with("\n")

                with open(musicPath, 'w') as file:
                    file.write(lyrics.text)

                print(f'File {music}.txt saved succefully!')
        except Exception as e:
            print(f'Could NOT save music "{music}" due to {e.__class__}.')

async def main():
    for genre, artists in musicList.items():
        print(f'Getting genre {genre}...')
        for artist, artistData in artists.items():
            print(f'Getting artist {artist}...')
            
            path = f'{DATA_PATH}/{genre}/{artist}'
            os.makedirs(path, exist_ok = True)

            async with aiohttp.ClientSession() as session:
                ret = await asyncio.gather(*[get(path, artistData["url"], music, session) for music in artistData["discography"]])

            print('Artist done!')

        print(f'Genre {genre} done!')

asyncio.run(main())