
class Source :
    '''
    обертка для хранения информации об одном источнике
    '''
    def __init__(self, path, name = None, encoding='utf-8'):
        self.path = path
        self.name = name
        self.encoding = encoding
        self.cntr__referenced_words = 0
        self.ratio_sum__TX_IDE = 0

    def get_text(self, st_idx = 0, ed_idx = None):
        with open(self.path, mode='r', encoding= self.encoding) as file:
            original_text = file.read()
        text_part = ''
        f__next = False
        for idx, ch in enumerate(original_text):
            f__space_detected = ch == '\n' or ch ==' ' or idx == 0

            if f__space_detected and st_idx <= idx:
                f__next = True

            if f__space_detected and not ed_idx is None and ed_idx < idx :
                f__next = False

            if not f__next :
                continue

            text_part += ch
        return text_part

    def reference_word(self):
        self.cntr__referenced_words += 1

    def to_dict(self):
        return {
            'path':self.path,
            'name':self.name
        }

class Position :
    '''
    обертка для хранения информации о позиции (слова) в тексте
    '''
    base_num = -1
    def __init__(self, source:Source, idx__start, idx__end, num = None, f__clear = False):
        if f__clear:
            Position.base_num = -1

        self.idx__start = idx__start
        self.idx__end = idx__end
        if num is None:
            Position.base_num +=1
            num = Position.base_num
        self.num = num


        self.source = source

    def to_dict(self):
        return {
            'idx':{
                'start':self.idx__start,
                'end':self.idx__end
            },
            'num':self.num
        }


class Idx_Word :
    '''
    обертка для хранения информации об одном слове
    '''
    def __init__(self, name, num__unique, origin = None, f__sent_start = False):
        self.name = name
        self.origin = origin
        self.f__sentance_start = f__sent_start
        self.num__unique = num__unique
        self.sources = []
        self.positions = []

    def add_position(self, value: Position):
        self.positions += [value]
        if not value.source in self.sources:
            self.sources += [value.source]

    def get_positions_by_source (self, src: Source):
        return [item for item in self.positions if item.source == src]

    def get_TF(self, src: Source):
        total = src.cntr__referenced_words
        if total == 0 :
            return 0
        src_repeats = self.get_positions_by_source(src)
        repeats = len(src_repeats)
        freq = repeats / total
        return freq

    def get_IDE(self):
        return len(self.sources)

    def get_TF_IDE(self, src: Source):
        return self.get_TF(src) * self.get_IDE()

    def to_dict(self):
        return {
            'name':self.name,
            'num__unique':self.num__unique,
            'sources': [item.to_dict() for item in self.sources],
            'positions':[item.to_dict() for item in self.positions]
        }

def get_words_from_source( src : Source, words = None):
    '''

    формируется объект idx_word
    из текста стразу созраняются все возможные параметры в этот объект
    - начальный индекс (необработанного текста)
    - конечный индекс
    - все позиции в источнике
    - все источники (между вызовами так как ссылки на источники жесткие - не меняются)
    '''
    original_text = src.get_text().replace('\n',' ')
    if words is None :
        words = {}
    st_idx = 0
    f__clear = True
    for idx, char in enumerate(original_text):
        if not char == ' ':
            continue

        # чувствительные к st_idx
        f__sent_start = False
        origin_word = original_text[st_idx: idx]
        if origin_word == origin_word.capitalize():
            f__sent_start = True

        temp_word = origin_word.casefold()
        pos_it = Position(src, st_idx, idx, f__clear=f__clear)

        # изменение
        st_idx = idx +1
        if not temp_word.isalpha():
            continue
        if words.get(temp_word) is None:
            src.reference_word()
            words[temp_word] = Idx_Word(temp_word,len(words),origin_word, f__sent_start)

        if f__clear:
            f__clear = False

        words[temp_word].add_position(pos_it)

        st_idx = idx
    #return words.values()
    return words

def compute_min_summ_positions( request_str, d__words, src : Source ):
    '''
    расчет минимальных расстояний
    каждыый цикл этап развития (эволюции структуры данных)
    '''
    s_words = [item.casefold() for item in request_str.split(' ')]
    f_words = {}

    for s_word in s_words:
        if not d__words.get(s_word) is None :
            f_words[s_word] = {
                'origin': d__words[s_word],
                'src_positions':{}
            }

    for f_word in f_words.keys():
        for position in f_words[f_word]['origin'].positions:
            if src == position.source:
                f_words[f_word]['src_positions'][position.num] = {
                    'value':position, 'links':{}
                }
    '''  # структура данных 
    word : {
        'origin' : idx_word_obj
        'src_positions' : {
            'pos_num_1' : { #номер слова в тексте (общий)
                'value' : position_obj
                'links' : { ####### добавляется на следующем этапе
                    'word_1v' : { # другие слова из запроса
                        'difference' : int 
                        'origin' : position_obj # одна минимально близкая 
                            позиция из возможных вариатов этого слова 
                            из этого источника 
                    }
                    'word_2v' : ///
                }
            }
            'pos_num_2' : ///
        }
    }
    '''
    min_f_word_range_sum_pos = None
    for f_word in f_words.keys():
        for num__position in f_words[f_word]['src_positions'].keys():
            position = f_words[f_word]['src_positions'][num__position]['value']
            for f_word_out in f_words.keys():
                if f_word_out == f_word :
                    continue
                min_value__link = None
                for num__position_out in f_words[f_word_out]['src_positions'].keys():
                    position_out = f_words[f_word_out]['src_positions'][num__position_out]['value']
                    difference = abs(position_out.num - position.num)
                    if min_value__link is None or \
                            difference < min_value__link['difference']:
                        min_value__link = {
                            'difference':difference,
                            'origin':position_out
                        }

                f_words[f_word]['src_positions'][num__position]['links'][f_word_out] = min_value__link

            # расчет суммы расстояний
            total_sum = 0
            target_pos_its = f_words[f_word]['src_positions'][num__position]['links']
            if not target_pos_its is None:
                for key in target_pos_its.keys():
                    if not target_pos_its[key] is None :
                        total_sum += target_pos_its[key]['difference']
            if total_sum == 0:
                continue
            #f_words[f_word]['src_positions'][num__position]['range_sum'] = sum(target_pos_its)

            # сразу формируется контейнер для отправки
            # все ссылки на другие слова имеют только одну позицию (целевую - уже выбранную)
            if min_f_word_range_sum_pos is None or \
                total_sum < min_f_word_range_sum_pos['min_total_sum']:
                min_f_word_range_sum_pos = {
                    'min_total_sum':total_sum,
                    'f_word':f_words[f_word]['origin'],
                    'position':f_words[f_word]['src_positions'][num__position]['value'],
                    'linked__f_words':f_words[f_word]['src_positions'][num__position]['links'],
                }

    return min_f_word_range_sum_pos

def get_text_snippet_by_min_range( src: Source, min_sum_pos : dict,
                                   accept_range : int = 200, f__context : bool = True,
                                   context_len : int = 40, f__highlight : bool = True):
    '''
    {
        name,
        position
    }

    все данные уже собраны на начальном этапе
    на вход приходит уже структура данных с выбранными позициями
    из них достаются индексы в тексте.

    '''
    parent = {
        'name':min_sum_pos['f_word'].name,
        'position':min_sum_pos['position']
    }
    children = []
    for name in min_sum_pos['linked__f_words'].keys():
        children.append({
            'name':name,
            'position':min_sum_pos['linked__f_words'][name]['origin']
        })
    pos_it__s = [parent] + children
    pos_it__s.sort(key = lambda x: x['position'].num)
    target_idx = len(pos_it__s) -1
    while True:
        if pos_it__s[target_idx]['position'].num - \
                pos_it__s[0]['position'].num < accept_range:
            break
        target_idx -= 1

    st_idx = pos_it__s[0]['position'].idx__start
    ed_idx = pos_it__s[target_idx]['position'].idx__end
    if f__context :
        st_idx -= context_len
        ed_idx += context_len
    snippet = src.get_text(st_idx, ed_idx)
    if f__highlight:
        for item in pos_it__s:
            snippet = snippet.replace(
                item['name'], f'__{item["name"]}__'
            )

    return f'... {snippet} ...'
