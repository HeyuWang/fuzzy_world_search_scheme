import os

class RecordFileSize:
    def record(self,dirname):
        arr = os.listdir(dirname)
        size = []
        # text = []
        for f in arr:
            f = dirname+'/'+f
            fsize = os.path.getsize(f)
            size.append(fsize)
            # text.append((f,fsize))
        size.sort()
        return size




if __name__ == "__main__":
    test = RecordFileSize()
    # dirname = "./dataset_wildcard"
    dirname = "./dataset_adjacent"
    res = test.record(dirname)
    print(res)