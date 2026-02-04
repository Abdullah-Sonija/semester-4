class Staff:

    def __init__(self,name,id,dept):
        self.s_name = name
        self.s_id = id
        self.s_dept = dept

    def display_info(self):
        print(self.s_name," | ",self.s_id," | ",self.s_dept)

class Teachers(Staff):

    def __init__(self, name, id, dept,courses,salary):
        super().__init__(name,id,dept)
        self.courses = courses
        self.salary = salary

    def teach_courses(self,course_name):
        if course_name in self.courses:
            print(f"{self.s_name} is now teaching {course_name}.")
        else:
            print(f"{self.s_name} is not teaching {course_name}.")

    def display_info(self):
        super().display_info()
        print(f"Role: Teacher | Courses: {', '.join(self.courses)} | Salary: {self.salary}")

class Adminstrative_staff(Staff):

    def __init__(self, name, id, dept,role,w_hr):
        super().__init__(name, id, dept)
        self.roles = role
        self.working_hours = w_hr

    def perform_task(self,task):
        if task in self.roles:
            print(f"{self.s_name} is now performing {task}.")
        else:
            print(f"{self.s_name} is not perfoming {task}.")

    def display_info(self):
        super().display_info()
        print(f"Role: Adminstrative Staff | Roles: {', '.join(self.roles)} | Working hours: {self.working_hours}")

class Research_assitants(Staff):
    def __init__(self, name, id, dept,topics,stipend):
        super().__init__(name, id, dept)
        self.research_topics = topics
        self.stipend = stipend

    def work(self,research):
        if research in self.research_topics:
            print(f"{self.s_name} is now researching on {research}.")
        else:
            print(f"{self.s_name} is not researching on {research}.")

    def display_info(self):
        super().display_info()
        print(f"Role: Research Assitants | Research topics: {', '.join(self.research_topics)} | Stipend: {self.stipend}")

admin = Adminstrative_staff("Sarah", "A402", "HR", ["Hiring", "Payroll"], 40)
admin.display_info()
admin.perform_task("Hiring")