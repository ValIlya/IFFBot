import pytest
from iffbot.story import DFrotz


@pytest.mark.asyncio
async def test_dfrotz():
    game = DFrotz(
        dfrotz="bin/dfrotz",
        game="stories/LostPig.zblorb",
        savefile="a.save",
    )
    text = await game.start()
    assert text != ""
    await game.do("save")
    text = await game.do("e")
    assert text != ""
    text = await game.do("look around")
    assert text != ""
