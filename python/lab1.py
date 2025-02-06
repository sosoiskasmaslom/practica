
import math
import sympy as sp

def F(x, y, z):

    if abs(z) > 1: return -1

    return (
        (
            math.tan(y**2) 
            + math.acos(z**2)
        )**0.5 
        / (
            x**2 
            + math.pi * x * y**5
            )
        )

def second():
    x, y, z = map(int, (input("Input 3 numbers for Ex 2: ").split()))
    print("Ex2: ")
    print(round(F(x, y, z), 3))

def second_second_one():

    x = sp.Symbol('x')

    f = (2 + (x**2 - 2*x)) / (1+x)

    f_1st_derivative = sp.diff(f, x, 1)
    f_2nd_derivative = sp.diff(f, x, 2)
    f_5th_derivative = sp.diff(f, x, 5)


    print("ex 2 sympy 1.")
    print(
        f_1st_derivative.simplify(),
        f_2nd_derivative.simplify(),
        f_5th_derivative.simplify(),
        sep='\n'
    )

def second_second_two():

    x, y, z = sp.symbols("x,y,z")
    f = (sp.ln(z**2) + sp.cos(y) + sp.sin(x)) / (z * x**2 * y**2)

    f_onebacktick_x = sp.diff(f, x, 1)
    f_onebacktick_y = sp.diff(f, y, 1)
    f_onebacktick_z = sp.diff(f, z, 1)

    f_twobacktick_x = sp.diff(f, x, 2)
    f_twobacktick_y = sp.diff(f, y, 2)
    f_twobacktick_z = sp.diff(f, z, 2)

    f_mixed_xy = sp.diff(f, x, y)
    f_mixed_zy = sp.diff(f, z, y)

    print("ex 2 sympy 2.")
    print(
        f_onebacktick_x.simplify(),
        f_onebacktick_y.simplify(),
        f_onebacktick_z.simplify(),
        f_twobacktick_x.simplify(),
        f_twobacktick_y.simplify(),
        f_twobacktick_z.simplify(),
        f_mixed_xy.simplify(),
        f_mixed_zy.simplify(),
        sep='\n'
    )

def third():

    x, y, z = sp.symbols("x,y,z")
    f = (
        (sp.tan(y**2) + sp.acos(z**2))**0.5
        / (x**2 + sp.pi * x * y**5)
    )

    dfdx = sp.diff(f, x, 1)
    dfdy = sp.diff(f, y, 1)
    dfdz = sp.diff(f, z, 1)

    dfdx2 = sp.diff(f, x, 2)
    dfdy3 = sp.diff(f, y, 3)
    dfdz4 = sp.diff(f, z, 4)

    dfdxy = sp.diff(f, x, y)
    dfdzy = sp.diff(f, z, y)
    dfdzx = sp.diff(f, z, x)
    dfdxz = sp.diff(f, x, z)

    print("Ex 3:")
    print(
        dfdx.simplify(),
        dfdy.simplify(),
        dfdz.simplify(),
        dfdx2.simplify(),
        dfdy3.simplify(),
        dfdz4.simplify(),
        dfdxy.simplify(),
        dfdzy.simplify(),
        dfdzx.simplify(),
        dfdxz.simplify(),
        sep="\n\n"
    )

if __name__ == '__main__':

    second() # 3 2 1
    print("")
    second_second_one()
    print("")
    second_second_two()
    print("")
    third()