
import sympy as sp

def check(func, quan):

    quantities = sp.symbols(quan)
    f = eval(func)
    print(sp.diff(f, quantities[0], quantities[1]).simplify())

def parse(file):

    try:
        func = open(file, 'r').read()
    except FileNotFoundError:
        print("File not found")
        return

    func = "".join([i for i in func if i != " "])
    quan = ",".join(
                    sorted(
                        set(
                            [i for i in func if ord(i) in range(97, 123)]
                        )
                    )
    )

    print(func)

    for let in quan.split(','):
        func = func.replace(
            let,
            f"quantities[{quan.split(',').index(let)}]"
        )

    
    print(quan)

    check(func, quan)

if __name__ == '__main__':

    parse("input.txt")