
def set_one():

    A = {1, 2, 3}
    B = {2, 3, 4}

    return (len(A&B))

def set_two():

    A = {1, 2, 3}
    B = {2, 3, 4}

    return (f'{A-B} {A|B}')

def set_three():

    section1 = {"Tom", "Bob", "Alice", "Tommy"}
    section2 = {"Alice","Bob","Andy", "Tom", "Mikky"}

    answers = [
        len(section1&section2),
        len(section1|section2),
        "является" if (section1&section2 == section1) else "не является",
    ]

    for i in range(len(answers)):
        return (f"{i+1}. {answers[i]}")

def set_four():

    people = [
        "Беляев",
        "Степанов",
        "Клочкова",
        "Клочкова",
        "Свиридова",
        "Конев",
        "Лосев",
        "Лосев",
        "Свиридова",
        "Баранов",
    ]

    themes = [
        "Особенности риска",
        "Математическая кибернетика",
        "Физика твердого тела",
        "Математика как наука",
        "Информатика как наука",
        "Проблемы облачного хранилища",
        "Математика в истории",
        "Химия твердого тела",
        "Физические процессы",
        "Биохимия",
    ]

    section = [
        "Физика и химия",
        "Математика и программирование",
        "Физика и химия",
        "Математика и программирование",
        "Математика и программирование",
        "Математика и программирование",
        "Математика и программирование",
        "Физика и химия",
        "Физика и химия",
        "Физика и химия",
    ]

    math = [
        people[i] for i in range(len(people))\
        if "Математика" in section[i]
    ]

    physic = [
        people[i] for i in range(len(people))\
        if "Физика" in section[i]
    ]

    answers = [
        len(set(themes)),
        len(set(section)),
        len(set(people)),
        len(set(math)&set(physic)),
        len(set(people))-len(set(math)&set(physic)),
    ]

    return "   ".join(
        [f"{i+1}. {answers[i]}" for i in range(len(answers))]
    )

def map_one(city = "Калининград"):

    country = {
        "Москва": "Россия",
        "Париж": "Франция",
        "Лион": "Франция",
        "Калининград": "Россия",
        "Минск": "Беларусь",
    }

    return (f'{city} - это {country[city]}')

def map_two(language = "русский"):

    country = {
        "русский": "Россия",
        "французский": "Франция",
        "греческий": "Кипр",
        "турецкий": "Кипр",
        "английский": "Сингапур",
        "китайский": "Сингапур",
        "малайский": "Сингапур",
    }

    return (f'{language} - {country[language]}')

def map_three(word = "cat"):

    translator = {
        "cat": "кошка, кот",
        "dog": "собака",
        "home": "домашний каталог, дом",
        "mouse": "мышь, манипулятор мышка",
        "to do": "делать, изготавливать",
        "to produce": "производить",
        "sweet": "сладкий, милый",

        "кошка": "cat",
        "кот": "cat",
        "собака": "dog",
        "домашний каталог": "home",
        "дом": "home",
        "мышь": "mouse",
        "манипулятор мышка": "mouse",
        "делать": "to do",
        "изготавливать": "to do",
        "производить": "to produce",
        "сладкий": "sweet",
        "милый": "sweet",
    }

    return (f'{word} - {translator[word]}')

if __name__ == '__main__':

    exs = [
    [
        set_one(),
        set_two(),
        set_three(),
        set_four(),
    ],

    [
        map_one(),
        map_two(),
        map_three(),
    ]
    ]

    for i in range(len(exs)):
        for j in range(len(exs[i])):

            print(f'Ex. {i+1}.{j+1} - {exs[i][j]}')

