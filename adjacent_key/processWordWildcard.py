class processWordWildcard:
    def process_word(self,word):
        res = []
        res.append(word)
        for i in range(len(word)+1):
            temp = word[:i]+'*'+word[i:]
            res.append(temp)
        for i in range(len(word)):
            temp = word[:i]+'*'+word[i+1:]
            res.append(temp)
        return res
    
    def output_screen(self,word):
        r = self.process_word(word)
        for each in r:
            print(each)
    
    def output_to_file(self,word,file_name):
        with open(file_name,'a') as f:
            res = self.process_word(word)
            for each in res:
                f.write(each)
                f.write(' ')
            # f.write('\n')
    def output_carrige(self,file_name):
        with open(file_name,'a') as f:
            f.write('\n')



if __name__ == "__main__":
    test = processWordWildcard()
    test.output_screen("castle")