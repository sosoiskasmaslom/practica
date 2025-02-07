
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes

def write(file, text):

    with open(file, 'w') as inp:
        inp.write(str(text))

def encrypt(plain, publickey):

    enc = PKCS1_OAEP.new(publickey)
    cipher = enc.encrypt(bytes(plain, encoding="utf-8"))

    return cipher

def decrypt(cipher, privatekey):

    enc = PKCS1_OAEP.new(privatekey)
    plain = str(enc.decrypt(cipher), encoding="utf-8")

    return plain

if __name__ == "__main__":

    privatekey = RSA.generate(2048)
    publickey = privatekey.publickey()
    write("RSA_private.bin", bytes(privatekey.exportKey('PEM')))
    write("RSA_public.pem", bytes(publickey.exportKey('PEM')))
    
    cipher = encrypt(input(), publickey)
    print(cipher)
    print(decrypt(cipher, privatekey))