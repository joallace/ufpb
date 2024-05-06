import re
import unidecode
from bs4.element import ResultSet
# from scraper import *


def clean_genre(genre: str) -> str:
    """
    Cleans a given genre from Wikipédia.
    :param genre: String formatted genre.
    :return: Cleaned string formatted genre.
    """
    genre = genre.lower()
    genre = re.split(',', genre, maxsplit=1)[0]
    genre = re.sub(r'-|/', ' ', genre)
    genre = re.sub('music', '', genre)
    genre = re.sub(r'( )\1+', r'\1', genre)
    genre = genre[1 if genre[0]==' ' else None : -1 if genre[-1]==' ' else None]

    return genre

def clean_name(name: str, replaceAnd: bool = True) -> str:
    """
    Cleans a given name (song or artist).
    :param name: String formatted name.
    :return: Cleaned string formatted name.
    """
    name = unidecode.unidecode(name.lower())
    name = re.sub('&', 'and', name) if replaceAnd else name
    name = re.sub('\'', '', name)
    name = re.sub(r'[^a-z0-9]', '-', name)
    name = re.sub(r'(-)\1+', r'\1', name)
    name = name[1 if name[0]=='-' else None : -1 if name[-1]=='-' else None]
    
    return name


def clean_lyrics(fragments: ResultSet) -> str:
    """
    Transforms a set of fragments into cleaned lyrics.
    :param fragments: Fragments resulted from BeautifulSoup find_all().
    :return: Cleaned string formatted lyrics, returns None if there is no fragments.
    """
    if fragments:
        for fragment in fragments:
            for br in fragment.find_all("br"):
                br.replace_with("\n")

        lyrics = '\n'.join([fragment.text for fragment in fragments])
        
        if fragments[0]['class'][0] == 'lyrics':
            lyrics = re.sub(r'(\n){2}', '\n', lyrics)
            lyrics = lyrics[1:-1]

        lyrics = re.sub('’', '\'', lyrics)

        return lyrics
    else:
        return None

def clean_artist(name: str) -> str:
    name = unidecode.unidecode(name.lower().strip())
    
    return name