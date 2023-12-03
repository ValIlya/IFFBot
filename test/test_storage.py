import pytest
from iffbot.storage import UserStory, default_story


@pytest.mark.asyncio
async def test_user_story():
    story = UserStory(
            user='test',
            storyfile=default_story,
        )
    text = await story.do("e")
    assert text != ""
    text = await story.do("/translate")
    assert text != ""
