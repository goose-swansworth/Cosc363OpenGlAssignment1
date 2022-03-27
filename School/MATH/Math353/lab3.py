import matplotlib.pyplot as plt
import numpy as np
from numpy import array, linalg, zeros 

def newton_div_diff_wrapper(nodes, i, j):
    """Wrapper for recursive divided difference function so we can memoize"""
    cache = dict()
    def newton_div_diff(nodes, i, j):
        """Returns f[x_i,...,x_j]"""
        if (i, j) in cache:
            return cache[(i, j)]
        else:
            if i == j:
                return nodes[i][1]
            else:
                f_ij = (newton_div_diff(nodes, i + 1, j) - newton_div_diff(nodes, i, j - 1)) / (nodes[j][0] - nodes[i][0])
                cache[(i, j)] = f_ij
                return f_ij
    return newton_div_diff(nodes, i, j)


def newton_poly(nodes, x):
    out = 1
    for i in range(len(nodes)):
        xi = nodes[i][0]
        out *= (x - xi)
    return out
    

def intrp_poly_with_diffs(nodes, diffs, x):
    out = 0
    for k in range(len(nodes)):
        out += newton_poly(nodes[:k], x) * diffs[k]
    return out


nodes = [(2, np.log(2)), (2.5, np.log(2.5)), (3, np.log(3))]
diffs = []
for m in range(len(nodes)):
    f_m = newton_div_diff_wrapper(nodes, 0, m)
    diffs.append(f_m)
    print(f_m)

xspace = np.linspace(-4, 4, 100)
plt.plot(xspace, [intrp_poly_with_diffs(nodes, diffs, x) for x in xspace], label="p(x)", color="tab:green")
xs = [nodes[i][0] for i in range(len(nodes))]
ys = [nodes[i][1] for i in range(len(nodes))]
plt.scatter(xs, ys, label="nodes")
plt.grid()
plt.legend(loc="best")
plt.show()



