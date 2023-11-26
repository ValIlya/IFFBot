from dataclasses import dataclass

from iffbot.story import DFrotz


@dataclass
class UserInfo:
    story: DFrotz
    language: str = "en"


default_story = "stories/LostPig.zblorb"


class Storage:
    """
    Possibly a database
    """

    def __init__(self) -> None:
        self.stories = {}
        self.users = {}

    def add_story(self, story_name: str, story_file: str):
        # TODO: download
        self.stories[story_name] = story_file

    def add_user(self, user: str, story_file: str):
        self.users[user] = UserInfo(
            story=DFrotz(
                game=story_file,
                savefile=user,
            ),
        )

    def get_user_info(self, user: str) -> UserInfo:
        if user not in self.users:
            self.users[user] = UserInfo(
                story=DFrotz(
                    game="stories/LostPig.zblorb",
                    savefile=user,
                ),
            )
        return self.users[user]
