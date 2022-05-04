import pathlib
import tkinter as tk
from tkinter import ttk
from tkinter import filedialog as fd

from pprint import pprint

import datetime

def time_mesurement (func):
    def proxy(*args, **kwargs):
        t1 = datetime.datetime.now()
        tmp = func(*args, **kwargs)
        t2 = datetime.datetime.now()
        res = t2-t1
        res = int(res.total_seconds())
        print(f'time_mesurement: выполнение {func.__name__} заняло {res} sec')
        return tmp
    return proxy

from index_search import *

class Main :
    def __init__(self,
                 chosen_source : tk.StringVar,
                 search_req : tk.StringVar
                 ):
        self.chosen_source = chosen_source
        self.search_req = search_req

    @time_mesurement
    def update_sources(self):
        '''
        индексация всех текстовых файлов из папки
          get_words_from_source — получает отдельные слова вместе с позицией в тексте
            за слово отвечает объект Idx_Word
            obj__word.get_TF(src), obj__word.get_IDE()
                функции чтобы из собранных данных в объекте сразу просчитать параметры

            гипотеза (о взаимодействии) : ссылки на источники во всей
                последующей программе сохраняются
        '''
        self.dir_path = pathlib.Path(self.chosen_source.get())
        self.sources = []
        for path in self.dir_path.iterdir():
            if path.suffix != '.txt':
                continue
            self.sources.append(Source(str(path)))

        self.d__word_capacitor = {}
        # жесткие ссылки
        for src in self.sources:
            self.d__word_capacitor = get_words_from_source(
                src, self.d__word_capacitor
            )

        for src in self.sources:
            sum__tx_ide_ratio = 0
            for key in self.d__word_capacitor.keys():
                obj__word = self.d__word_capacitor[key]
                tf_ratio = obj__word.get_TF(src)
                ide_ratio = obj__word.get_IDE()
                # сохраняется сразу в источник
                # дял каждого слова бессмысленно сохранять параметр
                #так как для разных источников отличается
                sum__tx_ide_ratio += tf_ratio*ide_ratio
            src.ratio_sum__TX_IDE = sum__tx_ide_ratio



    def get__TF_IDE_sources_list(self):
        '''
        обертка для 1го алгоритм (пункт а)
        возвращает подходящие источники
        (просчет параметров объектов происходит в update_sources
            здесь только их извлечение)
        * логика в файле index_search

        сортировка в порядке уменьшения показателя
        '''
        self.sources.sort(key=lambda x: x.ratio_sum__TX_IDE, reverse=True)
        return self.sources

    def get__MinRange_sources_list_by_request(self):
        '''
        2й алгоритм (пункт б)
        возвращает подходящие источники
        * логика в файле index_search

        одновременно расчитывает минимальную сумму расстояний
        вместе добавляет к выводу сниппет
        сортировка в порядке увеличения показателя
        '''
        request_str = self.search_req.get()
        if request_str == '':
            return None
        min_pos__l = []
        for src in self.sources:
            min_pos__s = compute_min_summ_positions(
                request_str,
                self.d__word_capacitor,
                src
            )
            if min_pos__s is None:
                continue

            text_snippent = get_text_snippet_by_min_range(
                src, min_pos__s
            )

            min_pos__l.append({
                'value': min_pos__s,
                'min_range_sum':min_pos__s['min_total_sum'],
                'source': src,
                'snippet':text_snippent
            })
        min_pos__l.sort(key=lambda x: x['value']['min_total_sum'])
        return min_pos__l

class Chose_folder_button:
    '''
    Выбор папки с индексируемыми файлами
     сразу после выбора их индексирует
    при завершении загоряется зеленым
    в начале индексации возвращается на серый
    '''
    def __init__(self, Frame, main_obj = None):
        self.value = tk.StringVar()
        self.main_obj = main_obj
        self.obj = tk.Button(
            Frame,
            text='Выбрать папку с ресурсами',
            command=self.chose_folder,
            bg='light grey'
        )
        self.obj.grid(row=0, column=0, sticky='we')

    def chose_folder (self):
        self.obj.configure(bg='light grey')
        self.value.set(fd.askdirectory())
        self.main_obj.update_sources()
        self.obj.configure(bg='lawn green')

class Url_input:
    def __init__(self, Frame):
        self.value = tk.StringVar()
        tk.Entry(
            Frame, textvariable=self.value
        ).grid(
            row=0, column=1, sticky=(tk.W + tk.E)
        )

# вывести индексы
class index_radiobutton:
    '''
    выбор метода вывода
    '''
    def __init__(self, Frame):
        self.value = tk.StringVar()
        ttk.Radiobutton(
                Frame,
                value='TF_IDX index for source',
                text='TF_IDX index for source',
                variable=self.value
            ).pack(side=tk.LEFT, expand=True)
        ttk.Radiobutton(
                Frame,
                value='min range with snippet',
                text='min range with snippet',
                variable=self.value
            ).pack(side=tk.LEFT, expand=True)

    def get_state(self):
        return self.value.get()

class Show_button:
    '''
    логика вывода в консоль при всех введенных параметрах

    TF_IDX index for source - не зависит от поискового запроса
    '''
    def __init__(self, Frame, mode_val, main_obj):
        self.main_obj = main_obj
        self.mode_val = mode_val
        tk.Button(
            Frame,
            text='Вывести',
            command=self.show_result,
            bg='light grey'
        ).pack(side=tk.LEFT, expand=True)

    @time_mesurement
    def show_result(self):
        res = None
        match self.mode_val.get():
            case 'TF_IDX index for source':
                print('search — TF_IDX index for source')
                res = self.main_obj.get__TF_IDE_sources_list()
                for num, item in enumerate(res):
                    if num > 4:
                        break
                    print(f'{num} — {item.path} \n\t (RF*IDE summ = {item.ratio_sum__TX_IDE})')
            case 'min range with snippet':
                print('search — min range with snippet')
                res = self.main_obj.get__MinRange_sources_list_by_request()
                if res is None :
                    print('search request is empty')
                    return
                for num, item in enumerate(res):
                    if num > 4:
                        break
                    print(f'{num} — {item["source"].path} \n\t(min range summ (all from indexed words)= {item["min_range_sum"]})')
                    pprint(f'\t{item["snippet"]}')
            case _ :
                print('no output option')

root = tk.Tk()
root.columnconfigure(0, weight=1)


sec_1v = ttk.Frame(root)
sec_1v.grid(sticky=(tk.E + tk.W))
sec_1v.columnconfigure(0, weight=1)
sec_1v.columnconfigure(1, weight=2)
chose_button = Chose_folder_button(sec_1v)
#автоматически обновляет источники при выборе папки
search_inp = Url_input(sec_1v)

main_obj = Main(
    chose_button.value,
    search_inp.value
)
chose_button.main_obj = main_obj

sec_2v = ttk.Frame(root)
sec_2v.grid(sticky=(tk.E + tk.W))
sec_2v.columnconfigure(0, weight=2)
sec_2v.columnconfigure(0, weight=1)
chose_mode = index_radiobutton(sec_2v)
show = Show_button(
    sec_2v,
    chose_mode.value,
    main_obj
)

root.geometry(f'500x50')
root.title('расчет поисковых параметров')
root.mainloop()