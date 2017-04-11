#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Thu Apr  6 11:04:04 2017

@author: tim
"""
    


if __name__ == '__main__':
    import numpy as np
    import matplotlib.pyplot as plt
    from matplotlib.animation import FuncAnimation
    from sys import argv
    #30000:2 'size': 'ticks' with default window size

    fname = argv[1]
    try:
        genStart = int(argv[2])
    except:
        genStart = 0

    f = open(fname, 'rt')
    foodCount = int(np.fromfile(f, dtype = np.uint64, count = 1))
    autCount =  int(np.fromfile(f, dtype = np.uint64, count = 1))
    updatesPerSim =  int(np.fromfile(f, dtype = np.uint64, count = 1))
    numGens = int(np.fromfile(f, dtype = np.uint64, count = 1))
    
    xmin = float(np.fromfile(f, dtype = np.float64, count = 1))
    xmax = float(np.fromfile(f, dtype = np.float64, count = 1))
    ymin = float(np.fromfile(f, dtype = np.float64, count = 1))
    ymax = float(np.fromfile(f, dtype = np.float64, count = 1))
    print xmin, xmax, ymin, ymax
    print foodCount
    print autCount
    print updatesPerSim
    print numGens
    totalCount = foodCount + autCount
    np.fromfile(f, dtype = np.float64, count = 3 * totalCount * updatesPerSim * genStart)
    


    fig, ax = plt.subplots()
    scat = ax.scatter([0] * totalCount, [0] * totalCount)
    plt.xlim((xmin, xmax))
    plt.ylim((ymin, ymax))
    def update(n):
        data = np.fromfile(f, dtype = np.float64, count = 3 * totalCount)
       

        data = data.reshape((totalCount, 3))
        xposns = [org[0] for org in data]
        yposns = [org[1] for org in data]
        ax.cla()
        scat = ax.scatter(xposns, yposns)
        scat._sizes = ((10 * np.array([float(org[2]) for org in data])) **2 )
        print np.array([float(org[2]) for org in data])
        plt.xlim((xmin, xmax))
        plt.ylim((ymin, ymax))
        return scat
    ani = FuncAnimation(fig, update, 300, interval=10)
    plt.show()

    
    
    
    