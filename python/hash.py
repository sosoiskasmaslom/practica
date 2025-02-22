import hashlib, bcrypt

def first(name):
    for alg in hashlib.algorithms_available:
        h = hashlib.new(alg)
        h.update(name.encode())
        try: yield alg, h.hexdigest()
        except TypeError: yield alg, h.hexdigest(len(name)**2)

def second(login, password):
    
    hlogin = bcrypt.hashpw(login.encode(), bcrypt.gensalt())
    hpassword = bcrypt.hashpw(password.encode(), bcrypt.gensalt())
    if bcrypt.checkpw(login.encode(), hlogin) and \
       bcrypt.checkpw(password.encode(), hpassword): 
        return " ".join([str(hlogin), str(hpassword)])
    else: return "Error"

def third(password):
    return bcrypt.hashpw(password.encode(), bcrypt.gensalt())
    # звучит как прикол

if __name__ == "__main__":

    r = 1

    print("First exercise")
    [print(i) for i in first(input("enter your name: "))]
    print('\n'*r)

    print("Second exercise")
    print(second(input("enter your login: "), input("enter your password: ")))
    print('\n'*r)

    print("Third exercise")
    print(third(input("enter your password: ")))