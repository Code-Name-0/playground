import sys
from PyQt5.QtWidgets import QApplication
import numpy as np
import matplotlib.pyplot as plt

np.seterr(all="ignore")

def get_screen_dpi():
    app = QApplication(sys.argv)
    screen = app.screens()[0]
    dpi = screen.physicalDotsPerInch()
    app.quit()
    return int(dpi)




def complex_matrix(maxx, maxy, minx, miny, pixel_density):
    re = np.linspace(minx, maxx, (maxx-minx)*pixel_density)
    im = np.linspace(miny, maxy, (maxy-miny)*pixel_density)

    return re[np.newaxis, :] + im[:,np.newaxis] * 1j


def is_stable(c,num_iteration):
    z = 0
    for _ in range(num_iteration):
        z = z ** 2 + c
    return abs(z) <= 2


def get_members(c, iterations):
    mask = is_stable(c, iterations)
    return c[mask]



dpi = get_screen_dpi()
complex_mat = complex_matrix(10, 10, -10, -10, int(dpi*2.5))

members = get_members(complex_mat, 50)

#plt.scatter(members.real, members.imag, color="black", marker=",", s=1)
plt.imshow(is_stable(complex_mat, 20), cmap="binary")
plt.gca().set_aspect("equal")
#plt.axis("off")
#plt.tight_layout()
plt.show()
