#! /usr/bin/env python3

import re

traceFile = open('./ls-trace.txt', 'r')
vpnFile = open('./vpn.txt', 'w')

ADDR_REGEX = re.compile(r'^[a-zA-Z0-9]{1} *(\d*),\d*$')

for line in traceFile:
    addr_match = ADDR_REGEX.fullmatch(line.strip())
    if not addr_match:
        continue
    address = addr_match.group(1)
    vpnFile.write(str((int("0x" + address[3:11], 16) & 0xfffff000) >> 12) + "\n")

traceFile.close()
vpnFile.close()

