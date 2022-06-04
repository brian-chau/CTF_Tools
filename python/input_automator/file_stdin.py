#!/usr/bin/python3

import subprocess as sp

file = open('/tmp/edbqfo')
proc = sp.Popen(['/challenge/embryoio_level19'], stdin=file)
proc.communicate()
proc.wait()
file.close()
