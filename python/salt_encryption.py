
from Crypto.Random import get_random_bytes
from Crypto.Protocol.KDF import PBKDF2

def write(file, text):

    with open(file, 'w') as inp:
        inp.write(str(text))

if __name__ == "__main__":
    salt = get_random_bytes(32)
    key = PBKDF2(input(), salt, dkLen=32)
    write("output_key.txt", key)