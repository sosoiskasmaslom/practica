
aliases = {
    "0": "",
    "1": "один",
    "2": "два",
    "3": "три",
    "4": "четыре",
    "5": "пять",
    "6": "шесть",
    "7": "семь",
    "8": "восемь",
    "9": "девять",
    "10": "десять",
    "40": "сорок",
    "90": "девяносто",
    "100": "сто",
    "200": "двести",
    "1000": "тысяча"
}


def num2let(n: str, sym=' '):

    res = []
    i = len(n)

    if n == "0": return "ноль"

    for l in n:
        i -= 1
    
        if (l == "0"): continue

        if (i == 0):
            res.append(aliases[l])

        elif (i == 1):
            if (aliases[n[i]] == ""):
                res.append(aliases["10"])
                break
            elif (l == "1"): 
                fucku = aliases[n[i]].replace("а", "е")
                if n[i] in "123":
                    fucku += "."
                res.append(fucku[:-1]+"надцать")
                break
            elif (l in "23"):
                res.append(aliases[l]+"дцать")
            elif (l in "5678"):
                res.append(aliases[l]+"десят")
            else: res.append(aliases[l+'0'])

        elif (i == 2):
            if (l in "34"):
                res.append(aliases[l]+"ста")
            elif (l in "56789"):
                res.append(aliases[l]+"сот")
            else:
                res.append(aliases[l+"00"])
        
        elif (i == 3):
            if (l == "1"):
                res.append(aliases[l+"000"])
            else:
                res.append(
                    aliases[l]
                    + ' '
                    + aliases["1000"][:-1]
                    + 'и'
                )

    return sym.join(res)

if __name__ == "__main__":
    inp = input().rstrip()
    
    if 1 not in [1 if (i not in "0123456789") else 0 for i in inp]:
        print(num2let(inp))
    else: print("error")

