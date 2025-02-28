# thank you, copilot

class MineralWater:
    def __init__(self, addition=None):
        self.addition = addition

    def show_my_dish(self):
        if self.addition in ["Сироп", "топинг", "ваниль"]:
            print(f"Блюдо и {self.addition}")
        else:
            print("Блюдо без добавки")

class Student:
    def __init__(self, surname, specialty):
        self.surname = surname
        self.specialty = "Математические методы защиты информации"
        if specialty != self.specialty:
            print(f"Вы ошибаетесь. Ваша специальность: {self.specialty}")

    def show_info(self):
        print(f"Фамилия: {self.surname}, Специальность: {self.specialty}")

# Пример использования класса MineralWater
water1 = MineralWater("Сироп")
water1.show_my_dish()

water2 = MineralWater()
water2.show_my_dish()

# Пример использования класса Student
student1 = Student("Иванов", "Русская филология")
student1.show_info()

student2 = Student("Петров", "Математические методы защиты информации")
student2.show_info()