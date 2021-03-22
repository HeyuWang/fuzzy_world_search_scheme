from processFileAdjacent import processFile as p
from processFileWIldcard import processFileWildcard as p1


if __name__ == "__main__":

    for i in range(1,11):
        batch_worker = p()
        batch_worker1 = p1()
        file_post = str(25*i)
        INfilename = "./dataset/"+file_post
        OUTfilename = "./dataset_adjacent/"+file_post
        OUTfilename1 = "./dataset_wildcard/"+file_post
        batch_worker.generateFuzzyKeywordSet(INfilename,OUTfilename)
        batch_worker1.generateFuzzyKeywordSet_Wildcard(INfilename,OUTfilename1)