def calc_parity_bit(data, positions, length):

    parity = 0
    for i in range(positions, length, 2 * positions):
        parity ^= sum(data[i:i + positions])
    return parity % 2

def encode_hamming(data_bits):

    data_len = len(data_bits)
    r = 0
    while (2**r) < (data_len + r + 1):
        r += 1

    hamming_code = []
    j = 0
    for i in range(1, data_len + r + 1):
        if (i & (i - 1)) == 0:
            hamming_code.append(0)
        else:
            hamming_code.append(int(data_bits[j]))
            j += 1
    
    for i in range(r):
        parity_bit_pos = 2**i - 1
        parity_value = \
        calc_parity_bit(hamming_code, 2**i, len(hamming_code))
        hamming_code[parity_bit_pos] = parity_value

    return ''.join(map(str, hamming_code))

def decode_hamming(received_code):

    received_code = list(map(int, received_code))
    length = len(received_code)
    
    error_pos = 0
    for i in range(length):
        if received_code[i] == 1:
            error_pos ^= (i + 1)

    if error_pos != 0:

        print(f"Ошибка на позиции {error_pos}. Исправляем ошибку.")
        received_code[error_pos - 1] ^= 1
    
    data_bits = []
    for i in range(length):
        if (i + 1) & (i) != 0:
            data_bits.append(str(received_code[i]))
    
    return ''.join(data_bits)

if input() == '1':

    data_bits = \
    open('input.txt', 'r').read().strip()

    hamming_code = encode_hamming(data_bits)
    open('output.txt', 'w').write(hamming_code)

else: 

    received_code = open('received.txt', 'r').read().strip()
    decoded_bits = decode_hamming(received_code)
    open('decoded_output.txt', 'w').write(decoded_bits)
        
print("Программа завершена.")
