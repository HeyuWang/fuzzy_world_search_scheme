import os
class extract:
    
    def extract(self):
        print("please input W(w) or (a)\n")
        input1 = input()
        input1 = input1.lower()

        print("i got your first input\n please input your second parameter k, which stand for length_k\n")
        k = input()
        print("make sure it's a number")
        
        res = []

        if input1 == 'w':
            filename = "wildcard_time.txt"
            with open(filename) as f:
                for line in f:
                    target_str = "length "+k
                    if target_str in line:
                        splited_line = line.split()
                        res.append(float(splited_line[-2]))
            return res
        elif input1 == 'a':
            filename = "adjacent_time.txt"
            with open(filename) as f:
                for line in f:
                    target_str = "length "+k
                    if target_str in line:
                        splited_line = line.split()
                        res.append(float(splited_line[-2]))
            return res
        else:
            print("wrong input, restart the program\n")


if __name__ == "__main__":
    test = extract()
    res = test.extract()
    print(res)
