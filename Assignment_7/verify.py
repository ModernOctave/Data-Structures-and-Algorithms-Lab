# read lines from ts.txt
# each line is form of number number
# example:
# 1 2
# make dictionary with key as first number and value as second number

def main():
    d = {}
    with open('test.graph') as f:
        (n,e) = f.readline().split()
        for i in range(int(e)):
            (key, val) = f.readline().split()
            if int(key) in d:
                d[int(key)].append(int(val))
            else:
                d[int(key)] = [int(val)]
    # open ts.txt
    with open('ts.txt') as f:
        ans = []
        for line in f:
            ans.append(int(line.strip()))
    for element in ans:
        # check if element is in dictionary as key
        if element in d:
            for x in d[element]:
                if ans.index(element) > ans.index(x):
                    print(element, x)
                    print("FAIL")
                    exit()
    print("PASS")
        

main()