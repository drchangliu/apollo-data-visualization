# -*- coding: utf-8 -*-
'''
A prototype visualizer that use pptk

The downside of this is that it require
access to the actual monitor to view the
result.
'''
import os

import numpy as np
import pandas as pd
import pptk

base_path = ['..', '3d-sample', 'bin_files']
filename = '002_00000000.bin'

if __name__ == '__main__':

    '''
    # Sample visualization.
    xyz = pptk.rand(100, 3)
    v = pptk.viewer(xyz)
    v.set(point_size=0.005)
    v.wait()
    '''

    path = base_path + [filename]

    if not os.path.isfile(os.path.join(*path)):
        print('Could not find a file at "%s"' % os.path.join(*path))
        os.exit(-1)

    # Load the data from a file.
    names = ('x', 'y', 'z', 'i')
    offsets = (0, 4, 8, 12)
    formats = ('f4', 'f4', 'f4', 'f4')
    dt = np.dtype({
        'names': names,
        'offsets': offsets,
        'formats': formats,
    }, align=True)
    points = pd.DataFrame(np.fromfile(os.path.join(*path), dt))

    v = pptk.viewer(points[['x', 'y', 'z']])
    v.set(point_size=0.001)
    v.wait()
