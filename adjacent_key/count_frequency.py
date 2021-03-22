class countFrequency:
    def __init__(self):
        self.d = dict()
    
    def CF(self,filename):
        with open(filename,'r') as f:
            for line in f:
                list_line = line.split()
                for word in list_line[1:]:
                    word = word.lower()
                    length = len(word)
                    if length not in self.d:
                        self.d[length] = []
                        self.d[length].append(word)
                    else:
                        if word not in self.d[length]:
                            self.d[length].append(word)
        sorted(self.d.items(), key = lambda x:x[0])
        for k,v in self.d.items():
            if k==8:
                print(k,v)
                print("\n\n")

if __name__ == "__main__":
    dirname = "./dataset/"
    filename = "25"
    path = dirname+filename

    test = countFrequency()
    test.CF(path)










                    
        