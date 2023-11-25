import pygame_io as io
import sys
import blorb
import babel
import zcode

def checkgamefile(gamefile):
    gamefile.seek(0)
    id = gamefile.read(4)
    if id.decode('latin-1') == 'FORM': # The file is an IFF FORM file
        gamefile.seek(8)
        if gamefile.read(4).decode('latin-1') == 'IFRS': # The file is a Blorb resource file
            return 'blorb'
        else:
            return 'unknown'
    elif id.decode('latin-1') == 'GLUL':
        return 'glulx'
    elif id[0] >= 1 and id[0] <= 8:
        return 'zcode'
    else:
        return 'unknown'
  
def getcode(gamedata):
    release = (gamedata[2] << 8) + gamedata[3]
    serial = gamedata[0x12:0x18].decode('latin-1')
    return str(release) + '.' + serial


def getgame(filename):
    gamefile = open(filename, 'rb')
    gametype = checkgamefile(gamefile)
    assert gametype == 'blorb'
    blorbs = blorb.Blorb(filename)
    game = blorbs.getExec(0)
    code = getcode(game)
    print(code)

    setupmodules(blorbs, game)
    zcode.routines.execstart(setdebug=True)
    return game


def setupmodules(blorbs, game):
    global terpnum, title, transcriptfile

    iFiction = blorbs.getmetadata()
    if iFiction:
        title = babel.gettitle(iFiction)
        headline = babel.getheadline(iFiction)
        author = babel.getauthor(iFiction)
        print(title+'\n'+headline+'\n'+author)
    
    io.setup(width=0, height=0, b=[blorbs], title=title, foreground=(0,0,0,255), background=(255,255,255,255))

    zcode.use_standard = 3
    if zcode.memory.setup(game) == False:
        return False
    
    
    transcriptfile = False
    terpnum = None
    # set up the various modules
    zcode.game.setup()
    zcode.routines.setup()
    zcode.screen.setup()
    zcode.input.setup()
    zcode.output.setup([False, True, transcriptfile])

    zcode.objects.setup()
    

    zcode.optables.setup()
    zcode.sounds.setup(blorbs)
    zcode.header.setup()
    zcode.text.setup()
    if terpnum != None:
        zcode.header.setterpnum(int(terpnum))

    return True

getgame('stories/LostPig.zblorb')
