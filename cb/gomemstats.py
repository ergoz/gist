#! /usr/bin/env python3

import sys
import re

import plotly.plotly as py
from plotly.graph_objs import *

interval = 1 # seconds

if len(sys.argv) < 2 :
    print("specify the log file")
    sys.exit(1)

stats = []

def handler_memstats(line, dstr) :
    stats.append(eval(dstr))

matchers = [
  [ re.compile(r'.*\[Info\].*memstats(.*)'),
    handler_memstats ],
]

for line in open(sys.argv[1]).readlines() :
    for regx, fn in matchers :
        m = regx.match(line)
        if m : fn(m.group(), *m.groups())

def allocationGraph() :
    allocs, total = [], []
    heapalloc, heapsys, heapidle, heapinuse, heaprels = [], [], [], [], []
    for i, m in enumerate(stats) :
        total.append(m["TotalAlloc"]); allocs.append(m["Alloc"]);
        heapsys.append(m["HeapSys"])
        heapalloc.append(m["HeapAlloc"])
        heapidle.append(m["HeapIdle"])
        heapinuse.append(m["HeapInuse"])
        heaprels.append(m["HeapReleased"])

    x = list(range(1, len(stats)+1))
    mode, line = "lines+markers", Line(shape='spline')
    data = Data([
        Scatter(x=x, y=total, mode=mode, name="total-allocs", line=line),
        Scatter(x=x, y=allocs, mode=mode, name="allocs", line=line),
        Scatter(x=x, y=heapsys, mode=mode, name="heap-sys", line=line),
        Scatter(x=x, y=heapalloc, mode=mode, name="heap-allocs", line=line),
        Scatter(x=x, y=heapidle, mode=mode, name="heap-idle", line=line),
        Scatter(x=x, y=heapinuse, mode=mode, name="heap-inuse", line=line),
        Scatter(x=x, y=heaprels, mode=mode, name="heap-released", line=line),
    ])
    print(py.plot(data, filename='allocation-graph'))

def countGraph() :
    mallocs, frees = [], []
    for i, m in enumerate(stats) :
        mallocs.append(m["Mallocs"]); frees.append(m["Frees"]);

    x = list(range(1, len(stats)+1))
    mode, line = "lines+markers", Line(shape='spline')
    data = Data([
        Scatter(x=x, y=mallocs, mode=mode, name="mallocs", line=line),
        Scatter(x=x, y=frees, mode=mode, name="frees", line=line),
    ])
    print(py.plot(data, filename='count-graph'))

def gcPausetime() :
    pauseTimes = []
    [ pauseTimes.extend(m["PauseNs"]) for i, m in enumerate(stats) ]

    x = list(range(1, len(pauseTimes)+1))
    mode, line = "lines+markers", Line(shape='spline')
    data = Data([
        Scatter(x=x, y=pauseTimes, mode=mode, name="gc-stw", line=line)
    ])
    print(py.plot(data, filename='gc-pause-time-graph'))

allocationGraph()
countGraph()
gcPausetime()
