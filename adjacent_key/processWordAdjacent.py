class processWord:
    def __init__(self):
        self.d = dict()
        self.d['q'] = ('1','2','w','a')
        self.d['w'] = ('2','3','e','s','a','q')
        self.d['e'] = ('3','4','r','d','s','w')
        self.d['r'] = ('4','5','t','f','d','e')
        self.d['t'] = ('5','6','y','g','f','r')
        self.d['y'] = ('6','7','u','h','g','t')
        self.d['u'] = ('7','8','i','j','h','y')
        self.d['i'] = ('8','9','o','k','j','u')
        self.d['o'] = ('9','0','p','l','k','i')
        self.d['p'] = ('0','-','[',';','l','o')
        self.d['a'] = ('q','w','s','z')
        self.d['s'] = ('w','e','d','x','z','a')
        self.d['d'] = ('e','r','f','c','x','s')
        self.d['f'] = ('r','t','g','v','c','d')
        self.d['g'] = ('t','y','h','b','v','f')
        self.d['h'] = ('y','u','j','n','b','g')
        self.d['j'] = ('u','i','k','m','n','h')
        self.d['k'] = ('i','o','l',',','m','j')
        self.d['l'] = ('o','p',';','.',',','k')
        self.d['z'] = ('a','s','x')
        self.d['x'] = ('s','d','c','z')
        self.d['c'] = ('d','f','v','x')
        self.d['v'] = ('f','g','b','c')
        self.d['b'] = ('g','h','n','v')
        self.d['n'] = ('h','j','m','b')
        self.d['m'] = ('j','k',',','n')

        self.d['['] = ('p','-','=',']','\'',';')
        self.d[']'] = ('=','\\','\'','[')
        self.d[';'] = ('p','[','\'','/','.','l')
        self.d["'"] = ('[',']','/',';')
        self.d[','] = ('k','l','.','m')
        self.d['.'] = ('l',';','/',',')
        self.d['/'] = (';',"'",'.')


        # self.d['Q'] = ('1','2','w','a')
        # self.d['W'] = ('2','3','e','s','a','q')
        # self.d['E'] = ('3','4','r','d','s','w')
        # self.d['R'] = ('4','5','t','f','d','e')
        # self.d['T'] = ('5','6','y','g','f','r')
        # self.d['Y'] = ('6','7','u','h','g','t')
        # self.d['U'] = ('7','8','i','j','h','y')
        # self.d['I'] = ('8','9','o','k','j','u')
        # self.d['O'] = ('9','0','p','l','k','i')
        # self.d['P'] = ('0','-','[',';','l','o')
        # self.d['A'] = ('q','w','s','z')
        # self.d['S'] = ('w','e','d','x','z','a')
        # self.d['D'] = ('e','r','f','c','x','s')
        # self.d['F'] = ('r','t','g','v','c','d')
        # self.d['G'] = ('t','y','h','b','v','f')
        # self.d['H'] = ('y','u','j','n','b','g')
        # self.d['J'] = ('u','i','k','m','n','h')
        # self.d['K'] = ('i','o','l',',','m','j')
        # self.d['L'] = ('o','p',';','.',',','k')
        # self.d['Z'] = ('a','s','x')
        # self.d['X'] = ('s','d','c','z')
        # self.d['C'] = ('d','f','v','x')
        # self.d['V'] = ('f','g','b','c')
        # self.d['B'] = ('g','h','n','v')
        # self.d['N'] = ('h','j','m','b')
        # self.d['M'] = ('j','k',',','n')
# 设word长为l，该函数选择所有从l中删除一个字母后的可能, output l 种
    def delete_one_alpha(self,word):
        res = []
        for i in range(len(word)):
            res.append(word[:i]+word[i+1:])
        return res

# 交换临近的字母，输出 l-1 种
    def swap_adjacent_alpha(self,word):
        res = []
        for i in range(len(word)-1):
            list_word = list(word)
            list_word[i],list_word[i+1] = list_word[i+1],list_word[i]
            res.append(''.join(list_word))
        return res
# 替换其中一个  共 6 *l 种
    def substitute_one_alpha(self,word):
        res = []
        for i in range(len(word)):
            if not word[i].isdigit():
                d = self.d[word[i]]
                for substituted in d:
                    list_word = list(word)
                    list_word[i] = substituted
                    res.append(''.join(list_word))
        return res


    
# l中依次挑一个，repeat   output l 种
    def repeat_one_alpha(self,word):
        res = []
        for i in range(len(word)):
            res.append(word[:i]+word[i]+word[i]+word[i+1:])
        return res

# 在每个字母左右依次插入，总共 2l*6 = 12l
    def insert_left_right(self,word):
        res = []
        for i in range(len(word)):
                if not word[i].isdigit():
                    d = self.d[word[i]]
                    for inserted in d:
                        list_word1 = list(word)
                        list_word2 = list(word)
                        list_word1.insert(i,inserted)
                        list_word2.insert(i+1,inserted)
                        res.append(''.join(list_word1))
                        res.append(''.join(list_word2))
        return res

# l+l-1+6l+l+12l = 19L-1 量级
    def all_possible_typo(self,word):
        res = []
        res.append(word)
        res1 = self.delete_one_alpha(word)
        res2 = self.repeat_one_alpha(word)
        res3 = self.swap_adjacent_alpha(word)
        res4 = self.substitute_one_alpha(word)
        res5 = self.insert_left_right(word)
        for each in res1:
            if each not in res:
                res.append(each)
        for each in res2:
            if each not in res:
                res.append(each)
        for each in res3:
            if each not in res:
                res.append(each)
        for each in res4:
            if each not in res:
                res.append(each)
        for each in res5:
            if each not in res:
                res.append(each)
        
        return res
    
    def output_to_screen(self,word):
        res = self.all_possible_typo(word)
        for each in res:
            print(each)
        return res
    
    def output_to_file(self,word,file_name = "./typo_dataset"):
        with open(file_name,'a') as f:
            res = self.all_possible_typo(word)
            for each in res:
                f.write(each)
                f.write(' ')
            # f.write('\n')
    def output_carrige(self,file_name):
        with open(file_name,'a') as f:
            f.write('\n')