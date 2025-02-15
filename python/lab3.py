
from fnmatch import fnmatch

def decor(func):

    def wrapper():
        mass = []
        text  = f"Enter from keyboard for ex. {func.__name__}:\n"
        text += f"{func.__doc__}"
        print(text)
        while True:
            tmp = input()
            if not tmp: break
            mass.append(func(tmp.rstrip()))
        while None in mass: mass.remove(None)

        return '\n'.join(mass)

    return wrapper



def one(line):
    # Ввода нет
    return "\t".join([l.replace('/', '-') for l in line.split() if '/' in l])
    
def two(line):
    # Ввода нет
    return "\n" + "\n".join([l for l in line.split() if '@' in l])

@decor
def three(line):
    """Нужно вывести строки, в которых фрагмент «кот» присутствует в качестве подстроки не менее 2 раз."""
    return line if line.count("кот") >= 2 else None

def four(line):
    # Ввода нет
    return "\n".join(
        [
            (l+'.').strip() for l in line.split('.') 
            if ".кот." in l.replace(' ', '.').replace(',', '.')
        ]
    )

def five(line):
    # Ввода нет
    return "\n".join(
        [
            l for l in line.split()
            if l.count("".join(sorted(set(l), key=lambda d: l.index(d)))) > 1 
        ]
    )

def adv(word):
    return "".join(
        [
            word[i] if (i>1) else word[i==0] 
            for i in range(len(word))
        ]
    )

@decor
def six(line):
    """В каждой строке нужно поменять местами две первые буквы в каждом слове, состоящем из двух и более букв"""
    return " ".join(
                [
                    adv(l) if len(l) >= 2 else l for l in line.split()
                ]
            )

@decor
def seven(line):
    """Напишите функцию для валидации мобильного номера в международном формате."""
    patterns = [
        "+7(912)???-??-??", 
        "+7(912)???????", 
        "+7(912)???-????",
        "+7912???-??-??", 
        "+7912???????", 
        "+7912???-????",
    ]

    for pattern in patterns:
        if fnmatch(line, pattern):
            return f'{line}: {True}'

    else: return f'{line}: {False}'

def eight(line):
    # Ввода нет
    return " ".join([l for l in line.replace(",", "").split() if l!=l.lower()])

def nine(line):
    # Ввода нет
    return "\n".join(
        [
            l for l in line.split('"')
            if fnmatch(l, "https*.png") or fnmatch(l, "https*.jpg")
        ]
    )

def ten(line):
    # Ввода нет
    return "\n".join(
        [
            f'{time}: {
                0<= int(time.split(":")[0]) <= 24 
                and 0<= int(time.split(":")[1]) <= 60
                and len(time.split(":")[1]) == 2 
            }'
            for time in [l for l in line.split() if ":" in l]
        ]
    )


text_two = \
"""
becroutteujomoi-7630@yopmail.com 8258258858889999 pallutatratro-4156@yopmail.com 2581447
critoutroizefrau-7835@yopmail.com
23
2511363525
lafreulleudope-8856@yopmail.com
shanel22@hotmail.com 12212211
felicita_bergstrom@yahoo.com
################################
jaqueline.abernathy@yahoo.com
++++++++++++++++++++++++++++++++
aubree.streich@yahoo.com
###############################
nico.cummings@gmail.com
########------------##############
"""

text_four = \
"""
Живет у нас веселый кот Васька. Он у нас совсем недавно. Подобрали мы его на улице. Был он
грустный, худой и жалобно мяукал. Нам с папой стало его жалко, и взяли кота с собой. С тех пор он стал
веселым. Дали ему имя Васька. Он играет, мурлычет, бегает по квартире. Любит покушать. Однажды был
такой случай. Пришла мама с магазина. Я была в это время в школе, а папа с работы еще не пришел.
Поставила мама на пол сумку с продуктами. В это время зазвенел телефон и она побежала к аппарату. Мама
долго разговаривала по телефону. А когда вернулась за сумкой, то увидела интересную картинку. Сумка
свалилась на бок, а все продукты лежали на полу: молоко, масло, сосиски. Это кот Васька наш постарался.
Почти все он перепробовал, и масло, и сосиски, пакет молока только не смог прогрызть. Мама не стала его
ругать, ведь котик Васька все еще не забыл, как он голодал на улице. Она налила ему молока и дала доесть
сосиску. Он скоро забудет свои старые привычки, если будем заботиться о нем. А вечером она рассказала
нам с папой эту историю. Мы весело посмеялись и попросили кота Ваську больше так не делать. Думаю, он
нас понял.
"""

text_eight = \
"""
профессор Филипп Филиппович
Преображенский, Иван Арнольдович Борменталь – молодой доктор,
ассистент и ученик профессора, Полиграф Полиграфович Шариков, Фёдор –
швейцар дома и, наконец, Вяземская – заведующая культотделом.
"""

text_nine = \
"""
<meta property="og:locale" content="ru_RU">
<meta property="og:type" content="website">
<meta property="og:url" content="https://proglib.io/u/xenolarr/posts">
<meta property="og:site_name" content="Библиотека программиста">
<meta property="og:title" content="Ксения Кравченко">
<meta property="og:description" content=" Исследую все, что шуршит и шевелится в IT. ">
<meta property="og:updated_time" content="">
<meta property="og:image" content="https://static.proglib.io/img/site/frog.png">
<picture>
<source srcset="https://media.proglib.io/users/avatars/2023/04/24/4272.jpg " type="image.webp">
<source srcset="https://media.proglib.io/users/avatars/2023/04/24/472.jpg" type="image.jpg">
<img src https://media.proglib.io/7ce572.jpg" width="60" height="60">
</picture>
<link rel="apple-touch-icon" sizes="180x180" href="https://static.proglib.io/favicon/apple-touch-icon.png">
<link rel="icon" type="image/png" sizes="32x32" href="https://static.proglib.io/favicon/favicon-32x32.png">
<link rel="icon" type="image/png" sizes="16x16" href="https://static.proglib.io/favicon/favicon-16x16.png">
<link rel="manifest" href="https://static.proglib.io/favicon/site.webmanifest">
<figure class="social-square flex align-center valign-center">
<img src="http://static.proglib.io/favicon/sitefiles/google.png" loading="lazy" alt="Библиотека программиста -
лучшие материалы по программированию">
</figure>
</div>
"""

text_ten = \
"""
РАСПИСАНИЕ ПАССАЖИРСКИХ ПОЕЗДОВ В 2024 ГОДУ*
Купить билет
ИЗ КАЛИНИНГРАДА
Номер поезда Направление Отправление Прибытие Дни курсирования №30 «Янтарь» Калининград-Москва
13:03 8:54 Ежедневно, кроме 31 декабря №148 Калининград – Москва 20:35 24:12
"""


if __name__ == '__main__':
    exs = \
    [
    one("We arrive on NOV/25/2018 So you are welcome after 04/01/2018"),
    two(text_two),
    three,
    four(text_four),
    five(text_four),
    six,
    seven,
    eight(text_eight),
    nine(text_nine),
    ten(text_ten),
    ]

    for i in range(len(exs)):
        if type(exs[i]) == str:
            print(f'Ex. {i+1} - {exs[i]}')
        else:
            print(exs[i]())
        print("")

