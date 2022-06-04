import subprocess as sp

sp.run(['/path/to/bin', 'arg1', 'arg2'],input=b'stdin value goes here', env={'variable1':'value'})
