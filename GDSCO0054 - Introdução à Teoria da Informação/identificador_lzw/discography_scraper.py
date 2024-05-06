from bs4 import BeautifulSoup
from fake_useragent import UserAgent
import aiohttp
import asyncio
import json
import time
import os

from string_cleaner import clean_name


userAgent = UserAgent()
DISCOGRAPHIES_PATH = "discographies.json"
VAGALUME_URL = "https://www.vagalume.com.br"
ARTISTS_PATH = "artists.json"

discographies = {}
if(os.path.isfile(DISCOGRAPHIES_PATH)):
    print(f'{DISCOGRAPHIES_PATH} already found. Reading...')
    with open(DISCOGRAPHIES_PATH, 'r') as file:
        discographies = json.load(file)

genres = {}
with open(ARTISTS_PATH, 'r') as file:
    genres = json.load(file)

async def get(genre, url, lock, session):
    while(True):
        try:
            print(f'{VAGALUME_URL}{url}')
            async with session.get(url=f'{VAGALUME_URL}/{url}') as r:
                    soup = BeautifulSoup(await r.text(), "lxml")

                    if r.ok:
                        artist = soup.select_one('h1.darkBG > a').text
                        async with lock:
                            if artist in discographies[genre]:
                                return

                            discographies[genre][artist] = {
                                'url': url,
                                'discography': []
                            }

                            for music in soup.select("ol#alfabetMusicList > li > div > div > a"):
                                print(music)
                                music = music['href'][(len(url)+2):-5]
                                if music and music not in discographies[genre][artist]['discography']:
                                    discographies[genre][artist]['discography'].append(music)

                            if not discographies[genre][artist]['discography']:
                                del discographies[genre][artist]
                                print(f'Could not save artist {artist}...')
                                return
                            else:
                                print(f'Saved artist {artist}!')
                                return
                    else:
                        print(f"[{r.status}] Unable to scrape {url}")
                        return
        except asyncio.TimeoutError as e:
            print("Sleeping for a minute...")
            time.sleep(60)
            continue
        except Exception as e:
            print(f"Unable to get url {url} due to {e.__class__}.")
            return


async def main():
    lock = asyncio.Lock()
    for genre, artists in genres.items():

        print(f'Getting {genre} genre...')
        discographies[genre] = {}

        async with aiohttp.ClientSession() as session:
            ret = await asyncio.gather(*[get(genre, clean_name(artist, False), lock, session) for artist in artists])

        with open(DISCOGRAPHIES_PATH, 'w') as outfile:
            json.dump(discographies, outfile, ensure_ascii=False)

        print(f'Genre {genre} done: {len(discographies[genre])} artists!')

asyncio.run(main())