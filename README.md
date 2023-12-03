# IFFBot

https://python-poetry.org/docs/#installation

```shell
git clone --recurse-submodules https://github.com/ValIlya/IFFBot
```

Python 3.9+
```shell
poetry install
make -C frotz dumb
cp frotz/dfrotz ./bin
echo "<telegram-token>" > .token
```


```shell
poetry run bot
```

### Tests
```shell
poetry run pytest test
```
