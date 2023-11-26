from subprocess import Popen, PIPE

import os
from typing import Tuple


class DFrotz:
    """
    Simple interface to dfrotz
    """

    def __init__(
        self,
        game: str,
        savefile: str,
        dfrotz: str = "bin/dfrotz",
        dfrotz_args: Tuple[str] = ("-w100",),
    ):
        self.dfrotz = dfrotz
        self.game = game
        self.savefile = savefile
        self.dfrotz_args = dfrotz_args
        self.process = None
        self.break_char = ">"

    def start(self) -> str:
        self.process = Popen(
            [self.dfrotz, *self.dfrotz_args, self.game],
            stdin=PIPE,
            stdout=PIPE,
        )
        return self.read_output()

    def is_running(self) -> bool:
        return self.process != None

    def read_output(self):
        res = []
        while True:
            char = self.process.stdout.read(1).decode()
            if not char:
                break
            if char == self.break_char:
                break
            res.append(char)
        return "".join(res)

    def do(self, command: str) -> str:
        """
        pipe command to frotz

        @param string command, to be send to frotz-process
            special commands: quit, save, restore
        @return str
        """
        if not self.is_running():
            return "start the game first"
        output = self._special_commands(command)
        if output:
            return output

        self._exec(command)
        print(command)
        return self.read_output()

    def _exec(self, command: str):
        self.process.stdin.write((command + "\n").encode())
        self.process.stdin.flush()

    def _special_commands(self, command: str) -> str:
        if command in {"q", "quit"}:
            self.process.kill()
            self.process = None
            return "quited"
        elif command in {"save"}:
            self._exec("save")
            self.process.stdout.flush()
            if os.path.isfile(self.savefile):
                os.remove(self.savefile)
            self._exec(self.savefile)
            self.process.stdout.flush()
            return "saved"


if __name__ == "__main__":
    game = DFrotz(
        dfrotz="bin/dfrotz",
        game="stories/LostPig.zblorb",
        savefile="a.save",
    )
    print(game.start())
    print(game.do("save"))
    print(game.do("e"))
    print(game.do("look around"))
