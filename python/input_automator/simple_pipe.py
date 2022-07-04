#!/usr/bin/python3

import subprocess as sp
from time import sleep

a = sp.Popen(['cat'], stdin = sp.PIPE, stdout=sp.PIPE)
b = sp.Popen(['/challenge/embryoio_level52'], stdin=a.stdout)
# Answer: ukfmomce