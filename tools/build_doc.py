#!/usr/bin/env python3

import subprocess

YELLOW = '\033[1;33m'
WHITE = '\033[1;m'
BLUE = '\033[1;34m'
RED = '\033[1;31m'
GREEN = '\033[1;32'

def yellow(s):
    """Returns a version of s that would be printed in yellow in a shell."""
    return (YELLOW+s+WHITE)

def blue(s):
    """Returns a version of s that would be printed in blue."""
    return (BLUE+s+WHITE)


warnings = {}

print("Generating documentation, it could take a few minutes...")
proc = subprocess.Popen("doxygen", shell=True, stderr=subprocess.PIPE)

for line in proc.stderr:
    line = str(line, "utf-8").strip()
    if "warning" in line:
        (filename, line, message) = line.split("|")
        if filename in warnings:
            warnings[filename].append((line, message))
        else:
            warnings[filename] = [(line, message)]


warning_count = 0
for filename, messages in sorted(warnings.items()):
    print("{0}{1}{2}, {3} warnings".format(YELLOW, filename, WHITE, len(messages)))
    for l, m in sorted(messages, key=lambda tup:int(tup[0])):
        warning_count = warning_count + 1
        print("  {0}{1}{2} : {3}".format(BLUE, l, WHITE, m))


print("{0}{1} warnings{2}".format(warning_count==0 and GREEN or RED, warning_count, WHITE))
    

# Opens the result in a web browser
subprocess.Popen("xdg-open ./auto_doc/html/index.html", shell=True)


