import subprocess as sp
import sys

prompt_string = "What number would you like to guess?"

def terminated_read( fd, terminators ):
    buf = []
    while True:
        r = fd.read( 1 ).decode('utf-8')
        buf += r
        if r in terminators:
            break;
    return ''.join( buf )

def submit_input( process, input ):
    print(input)
    process.stdin.write((input + '\n').encode('utf-8'))
    process.stdin.flush()

def check_output( output ):
    return "Nope!" in output

def read_prompt( process ):
    output = ''
    send_next_input = True
    while prompt_string not in output:
        output = terminated_read( process.stdout, "?" ).strip()
        send_next_input = check_output( output )
        print( output )
    return send_next_input

if __name__ == '__main__':
    app = ['./vuln']
    if len( sys.argv ) > 1 :
        app = sys.argv[1:]

    proc = sp.Popen(app, shell=False, bufsize=0,
                    stdin = sp.PIPE,
                    stdout = sp.PIPE,
                    stderr = sp.PIPE)

    for i in range(1, 8196, 1):
        send_next_input = False
        while send_next_input == False:
            submit_input( proc, str(i) )
            send_next_input = read_prompt( proc )
