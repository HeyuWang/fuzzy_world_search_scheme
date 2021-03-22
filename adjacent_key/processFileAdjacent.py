from processWordAdjacent import processWord as p

class processFile:
    def __init__(self):

        self.added = dict()
    
    def generateFuzzyKeywordSet(self,inFileName,outFileName):
        with open(inFileName,'r') as IN:
        
            worker = p()

            for line in IN:
                list_line = line.split()
                for word in list_line[1:]:
                    word = word.lower()
                    # if word not in self.added:
                    #     print(word)
                    #     self.added.setdefault(word,1)
                    worker.output_to_file(word,outFileName)
                worker.output_carrige(outFileName)



if __name__ == "__main__":
    test = processFile()
    test.generateFuzzyKeywordSet("./dataset/3","./dataset_adjacent/3")
