from dataclasses import dataclass
from typing import Dict

from deep_translator import GoogleTranslator

from iffbot.story import DFrotz


@dataclass
class Translator:
    story_language: str = "en"
    target_language: str = "ru"
    cache = {}

    def translate(self, message: str) -> str:
        key = (self.target_language, message)
        if key not in self.cache:
            self.cache[key] = GoogleTranslator(
                source=self.story_language, target=self.target_language
            ).translate(message)
        return self.cache[key]


class UserStory:
    def __init__(
        self,
        user: str,
        storyfile: str,
        last_piece: str = "",  # for translation
        translator: Translator = Translator(),
    ) -> None:
        self.user = user
        self.story: DFrotz = DFrotz(
            game=storyfile,
            savefile=f"{user}.save",
        )
        self.last_piece = last_piece
        self.translator = translator

    async def do(self, command: str):
        if command == "/translate":
            if self.last_piece == "":
                return self.translator.translate("I forgot last message")
            return self.translator.translate(self.last_piece)
        if command == "/start":
            if self.story.is_running():
                text = await self.story.do("start")
            text = await self.story.start()
            self.last_piece = text
            return text
        if command.startswith("/lang"):
            try:
                lang = command.split()[1]
                self.translator.target_language = lang
                return self.translator.translate(f'Language is set to "{lang}"')
            except:
                return "Try `/lang ru'"

        if not self.story.is_running():
            return await self.story.start()
        text = await self.story.do(command)
        self.last_piece = text
        await self.story.do("save")
        return text


default_story = "stories/LostPig.zblorb"


class Storage:
    """
    Possibly a database
    """

    def __init__(self) -> None:
        # available to play story files
        self.story_files: Dict[str, str] = {}
        # current running stories
        self.users = {}

    def add_story(self, story_name: str, story_file: str):
        # TODO: download
        self.stories[story_name] = story_file

    def add_user(self, user: str, story_file: str = default_story):
        self.users[user] = UserStory(
            user=user,
            storyfile=story_file,
        )

    def get_user_story(self, user: str) -> UserStory:
        if user not in self.users:
            self.add_user(user)
        return self.users[user]
