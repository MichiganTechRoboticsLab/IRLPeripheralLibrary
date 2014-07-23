class colors:
    BLACK = '\033[30m'
    RED =  '\033[31m'
    GREEN = '\033[32m'
    CYAN =  '\033[33m'
    BLUE =   '\033[34m'
    PURPL = '\033[35m'
    BROWN = '\033[36m'
    LGREY = '\033[37m'
    FLASH = '\033[5m'
    END =   '\033[0m'
    hBLACK = '\033[40m'
    hRED =  '\033[41m'
    hGREEN = '\033[42m'
    hCYAN =  '\033[43m'
    hBLUE =   '\033[44m'
    hPURPL = '\033[45m'
    hBROWN = '\033[46m'
    hLGREY = '\033[47m'
    
def printError(x):
    print colors.RED + colors.FLASH + x + colors.END
    
def printSuccess(x):
    print colors.hGREEN + colors.LGREY + x + colors.END
    
def printInfo(x):
    print colors.hBLUE + colors.LGREY + x + colors.END