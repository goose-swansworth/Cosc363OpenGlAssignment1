import math as m
import numpy as np
import matplotlib.pyplot as plt
import sys
 
pi = m.pi
two_pi = 2*m.pi
 
 
def distance(x, y):
    """Return distance between 2d points x and y"""
    return m.sqrt((y[0] - x[0]) **2 + (y[1] - x[1])**2)
 
 
def find_start_t(f, point, ti, d, tol, rev=False):
    """Find the point on f that is d away from point"""
    t_step = tol*tol
    t = ti
    while abs(distance(point, f(t)) - d) > tol:
        if rev:
            t -= t_step
        else:
            t += t_step
    return t
 
 
def find_t_step(f, start_t, d, tol, rev=False):
    """Find t_step such that the distance between f(start_t) and f(start_t + t_step) is approximately d"""
    t_step = tol*tol
    t_curr = start_t + t_step
    start_point = f(start_t)
    while abs(distance(start_point, f(t_curr)) - d) > tol:
        if rev:
            t_curr -= t_step
        else:
            t_curr += t_step
    return t_curr - start_t
 
 
def medium_line(dist, tol, to_print=False, to_plot=False):
    line = []
 
    a = lambda t: (40*m.cos(t)-100, 40*m.sin(t)+20)
    b = lambda t: (-100+200*t, 60)
    c = lambda t: (50*m.cos(t)+100, 50*m.sin(t)+10)
    d = lambda t: (150, 10-50*t)
    e = lambda t: (40*m.cos(t)+110, 40*m.sin(t)-40)
    f = lambda t: (110-60*t, -80)
    g = lambda t: (40*m.cos(t)+50, 40*m.sin(t)-40)
    h = lambda t: (20*m.cos(t)+110, 20*m.sin(t)-40)
    eye = lambda t: (130, -40+50*t)
    j = lambda t: (30*m.cos(t)+100, 30*m.sin(t)+10)
    k = lambda t: (100-140*t, 40)
    l = lambda t: (20*m.cos(t)-40, 20*m.sin(t)+20)
 
    ti, tf = pi/2, 2*pi
    t_step = find_t_step(a, ti, dist, tol)
    curve = [a(t) for t in np.arange(ti, tf, t_step)]
    curve.reverse() #this part of the curve is drawn backwards
    line += curve
 
    ti, tf = 0, 1
    ti = find_start_t(b, line[-1], 0, dist, tol)
    t_step = find_t_step(b, ti, dist, tol)
    curve = [b(t) for t in np.arange(ti, tf, t_step)]
    line += curve
 
    ti, tf = pi/2, 0
    ti = find_start_t(c, line[-1], ti, dist, tol, rev=True)
    t_step = find_t_step(c, ti, dist, tol, rev=True)
    t_range = []
    t_curr = ti
    while t_curr > tf:
        t_range.append(t_curr)
        t_curr += t_step
    curve = [c(t) for t in t_range]
    line += curve
 
    ti, tf = 0, 1
    ti = find_start_t(d, line[-1], ti, dist, tol)
    t_step = find_t_step(d, ti, dist, tol)
    curve = [d(t) for t in np.arange(ti, tf, t_step)]
    line += curve
 
    ti, tf = 2*pi, 3*pi/2
    ti = find_start_t(e, line[-1], ti, dist, tol, rev=True)
    t_step = find_t_step(c, ti, dist*1.25, tol, rev=True)
    t_range = []
    t_curr = ti
    while t_curr > tf:
        t_range.append(t_curr)
        t_curr += t_step
    curve = [e(t) for t in t_range]
    line += curve
 
    ti, tf = 0, 1
    ti = find_start_t(f, line[-1], ti, dist, tol)
    t_step = find_t_step(f, ti, dist, tol)
    curve = [f(t) for t in np.arange(ti, tf, t_step)]
    line += curve
 
    ti, tf = 3*pi/2, 0
    ti = find_start_t(g, line[-1], ti, dist, tol, rev=True)
    t_step = find_t_step(g, ti, dist, tol, rev=True)
    t_range = []
    t_curr = ti
    while t_curr > tf:
        t_range.append(t_curr)
        t_curr += t_step
    curve = [g(t) for t in t_range]
    line += curve
 
    ti, tf = pi, 2*pi
    ti = find_start_t(h, line[-1], ti, dist, tol)
    t_step = find_t_step(h, ti, dist, tol)
    t_range = []
    t_curr = ti
    while t_curr < tf:
        t_range.append(t_curr)
        t_curr += t_step
    curve = [h(t) for t in t_range]
    line += curve
 
    ti, tf = 0, 1
    ti = find_start_t(eye, line[-1], ti, dist, tol)
    t_step = find_t_step(eye, ti, dist, tol)
    curve = [eye(t) for t in np.arange(ti, tf, t_step)]
    line += curve
 
    ti, tf = 0, pi/2
    ti = find_start_t(j, line[-1], ti, dist, tol)
    t_step = find_t_step(j, ti, dist, tol)
    t_range = []
    t_curr = ti
    while t_curr < tf:
        t_range.append(t_curr)
        t_curr += t_step
    curve = [j(t) for t in t_range]
    line += curve
 
    ti, tf = 0, 1
    ti = find_start_t(k, line[-1], ti, dist, tol)
    t_step = find_t_step(k, ti, dist, tol)
    curve = [k(t) for t in np.arange(ti, tf, t_step)]
    line += curve
 
    ti, tf = pi/2, pi
    ti = find_start_t(l, line[-1], ti, dist, tol)
    t_step = find_t_step(l, ti, dist, tol)
    t_range = []
    t_curr = ti
    while t_curr < tf:
        t_range.append(t_curr)
        t_curr += t_step
    curve = [l(t) for t in t_range]
    line += curve
 
    if to_print:
        for i in range(len(line) - 1):
            print(f"{distance(line[i], line[i + 1]):.3f}, ({line[i][0]:.3f}, {line[i][1]:.3f}), ({line[i+1][0]:.3f}, {line[i+1][1]:.3f})")
 
    if to_plot:
        xs = [line[i][0] for i in range(len(line))]
        ys = [line[i][1] for i in range(len(line))]
        plt.scatter(xs, ys)
        plt.show()
 
    return line
 
 
dist = float(sys.argv[1])
med_line = medium_line(dist, 10**-3, to_plot=True)
num_points = len(med_line)
write_file = open("mediumline.txt", "x")
write_file.write(f"{num_points} {dist}\n")
for point in med_line:
    write_file.write(f"{point[0]} {point[1]}\n")
write_file.close()