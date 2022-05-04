#Быстрая сортировка функционирует по принципу "разделяй и властвуй". 

def q(array, first, last): #Создадим фунцкию, которая будет возвращаться, чтобы двигатсья по массиву и будет вызываться рекурсивно.
    if first == last: #Если начало и конец массива равны, то часть массива отсортирована.
        return #Выходим с функции.
    point = qsort(array, first, last) #Переменная для запоминания границы разделенного массива.
    q(array, first, point) #Вызываем фунцкию для сортировки частей, независимых друг от друга.  
    q(array, point+1, last) #После сортировки левой части возврщаемся к правой части.

def qsort(array, first, last): #Фунцкия для сортировки массива.
    point = array[first] #Возьмем за опорный первый элемент.
    right = last
    left = first
    while (left < right): #Будем двигаться по массиву, пока границы не встретяться.
        if (array[right] < point): #Сравниваем правый и опорный элемент, пока правый не будет меньше.
            if (array[left] >= point): #После сравниваем левый и опорный, пока левый не будет больше или равен.
                print('Point:', point)
                array[left],array[right] = array[right], array[left] #Меняем элементы массива.
                #В левой часте будут элементы меньше опорного, а в правой больше или равен опорному.
                print(array)
                print('Left:', array[left], '\t', 'Right:', array[right], "\n")
                global size #Считываем кол-во замен.
                size +=1
            else:
                left += 1
        else:
            right -= 1
    return right


size = 0
array = []
number = input('Array values: ').split() #Размерность массива.
for i in number: #Цикл для преобразования типа данных string в integer.
    array.append(int(i))
q(array, 0, len(array)-1)
print ('Size:', size)


