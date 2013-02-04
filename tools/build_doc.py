#!/usr/bin/env python3

import subprocess

YELLOW = '\033[1;33m'
WHITE = '\033[1;m'
BLUE = '\033[1;34m'
RED = '\033[1;31m'

def yellow(s):
    """Returns a version of s that would be printed in yellow in a shell."""
    return (YELLOW+s+WHITE)

def blue(s):
    """Returns a version of s that would be printed in blue."""
    return (BLUE+s+WHITE)


warnings = []

print("Generating documentation, it could take a few minutes...")
proc = subprocess.Popen("doxygen", shell=True, stderr=subprocess.PIPE)

print("Parsing output...")
for line in proc.stderr:
    line = str(line, "utf-8")
    if "warning" in line:
        # Parse the line to extract filename and line number
        a = line.split(":")
        filename = a[0].split("/")[-1]
        warnings.append(yellow(filename)+":"+blue(a[1])+":".join(a[2:]))

print("".join(warnings))
print(RED+"{0} warnings !!".format(len(warnings))+WHITE)
