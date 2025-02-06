
def pascal(n = 3):
    angle = [[1]*(i+1) for i in range(n)]
    for i in range(2, n):
        for j in range(1, i):
            angle[i][j] = angle[i-1][j-1]+angle[i-1][j]
    return angle

def formating(angle):
    max_len = len(" ".join(angle[-1]))
    text = ''
    for i in range(len(angle)):
        text += ' '*int((max_len-len(" ".join(angle[i])))/2) \
                + " ".join(angle[i]) \
                + '\n'
    return text

print(
    formating(
        [
            [str(i) for i in a] 
            for a in pascal(int(input()))
        ]
    )
)