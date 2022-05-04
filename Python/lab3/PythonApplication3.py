#Функция для изменения значения предстоящих при нюансе:
def change(a,b,r):
    x = list(a) #Преобразуем в список
    #Меняем значение:
    del x[b]
    x.insert(b, str(r))
    #Считываем кол-во операций:
    global size
    size += 2
    return "".join(x)

#Функция для реализации алгоритма Spigot:
def spigot(arr,a):
    foo = 0 #Переменная для подсчета недействительных цифр
    pi = ""
    for i in range(a):
        summa = 0 #Сумма
        transfer = 0 #Перенос
        for j in range(len(arr)-1,-1,-1): #Начинаем цикл с конца
            denominator = j * 2 + 1 #Знаменатель
            summa = arr[j] * 10 + transfer
            arr[j] = summa % denominator #Вычисляем остаток
            transfer = int(summa / denominator) * j #Вычислем перенос

            global size
            size += 7 #Считываем кол-во операций


        arr[0] = summa % 10 #Перенос для конечного числа
        counter = int(summa / 10) #Цифра для подсчета числа pi
        size += 2
        #Учитывание того, что в нулевом столбце возмжна сумма >= 100, что при делении на 10 не дает цифру:
        if counter == 9:
            foo += 1
        elif counter == 10:
            counter = 0
            size += 1
            for l in range(1, foo+1):
                r = int(pi[i-l:i-l+1]) #Используем срез для нахождения числа перед 10 (уже 0)
                if r == 9:
                    r = 0
                else:
                    r += 1
                size += 1
                pi = change(pi,i-l,r) #Меняем значение предстоящего при появлении 10
            foo = 1
        else:
            foo = 1
        pi += str(counter) #Подсчитываем число pi
        size += 2 #Считываем кол-во операций
    return pi


a = int(input('Number of simbols after comma: ')) #Вводим кол-во знаков 
size = 0 #Переменная для считывания кол-во операций
arr = [] 

b = int((a*10)/3) #Размер списка
for i in range(b): #Первоначально добавляем в список все 2
    arr.append(2)
c = spigot(arr,a)    
print ("Pi number spigot method:", size, '\n')
print(c[:1] + "." + c[1:]) #Записываем "." после 3 для наглядности

