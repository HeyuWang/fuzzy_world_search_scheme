from processWordWildcard import processWordWildcard as p1


class processFileWildcard:
    def __init__(self):
        self.added1 = dict()

    def generateFuzzyKeywordSet_Wildcard(self,inFileName,outFileName):
        with open(inFileName,'r') as IN:
        
            worker = p1()

            for line in IN:
                list_line = line.split()
                for word in list_line[1:]:
                    word = word.lower()
                    # if word not in self.added1:
                    #     print(word)
                    #     self.added1.setdefault(word,1)
                    worker.output_to_file(word,outFileName)
                worker.output_carrige(outFileName)

    

if __name__ == "__main__":
    test = processFileWildcard()
    test.generateFuzzyKeywordSet_Wildcard("./dataset/3","./dataset_wildcard/3")