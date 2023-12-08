import asyncio
import io
from queue import Queue
from subprocess import Popen, PIPE

import os
from threading import Thread
from asyncio import sleep
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
        dfrotz_args: Tuple[str] = ("-w1000",),
    ):
        self.dfrotz = dfrotz
        self.game = game
        self.savefile = savefile
        self.dfrotz_args = dfrotz_args
        self.break_char = ">"
        self.process = None
        self.reading_thread = None
        self.output_queue = Queue()
        self.output_delay = 0.1

    async def start(self) -> str:
        self.process = Popen(
            [self.dfrotz, *self.dfrotz_args, self.game],
            stdin=PIPE,
            stdout=PIPE,
        )
        self.reading_thread = Thread(
            target=self._read_output, args=(self.process.stdout, self.output_queue)
        )
        self.reading_thread.start()
        return await self.read_output()

    def is_running(self) -> bool:
        return self.process != None

    @staticmethod
    def _read_output(output: io.BufferedReader, queue: Queue):
        for line in iter(output.readline, b""):
            queue.put(line.decode())
        output.close()

    async def read_output(self):
        await sleep(self.output_delay / 2)
        self.process.stdout.flush()
        await sleep(self.output_delay / 2)
        res = []
        while not self.output_queue.empty():
            res.append(self.output_queue.get())
        return "".join(res)

    async def do(self, command: str) -> str:
        """
        pipe command to frotz

        @param string command, to be send to frotz-process
            special commands: quit, save, restore
        @return str
        """
        if not self.is_running():
            return "start the game first"
        # output = self._special_commands(command)
        # if output:
        #     return output

        self._exec(command)
        print(command)
        return await self.read_output()

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
