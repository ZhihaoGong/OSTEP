#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

from subprocess import check_output

POLICIES = ['FIFO', 'LRU', 'OPT', 'UNOPT', 'RAND', 'CLOCK']

CACHESIZES = np.arange(1, 5)

hitRates = []

for cacheSize in CACHESIZES:
    hitRate = []
    for policy in POLICIES:
        result = check_output(["./paging-policy.py", "-c", "-p", policy, "-f", "./vpn.txt", "-C",
                               str(cacheSize)]).decode()
        hitRate.append(result)
    hitRates.append(hitRate)

for i in range(len(POLICIES)):
    plt.plot(CACHESIZES, hitRates[i])

plt.legend(POLICIES)
plt.margins(0)
plt.xticks(CACHESIZES, CACHESIZES)
plt.xlabel('Cache Size (Blocks)')
plt.ylabel('Hit Rate')
plt.savefig('workload.png', dpi=227)
