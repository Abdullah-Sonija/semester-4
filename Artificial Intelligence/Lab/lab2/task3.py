class BankAccount:
    def __init__(self,owner,balance=0):
        self.__balance = balance
        self.owner = owner

    def deposit(self,amount):
        if amount < 0:
            return "Invalid amount"
        self.__balance += amount
        return f"{self.owner} deposited ${amount}. New balance: ${self.__balance}"
    
    def withdraw(self,amount):
        if amount < 0:
            return "Error: Withdrawal must be positive."
        if self.__balance - amount < 0:
            return f"{self.owner} has insufficient funds! Current balance: ${self.__balance}"
        else:
            self.__balance -= amount
            return self.__balance
    
    def get_balance(self):
        return f"{self.owner}'s Current Balance: ${self.__balance}"    

acc1 = BankAccount("abdullah", 10000)
acc2 = BankAccount("karamat")

print(acc1.deposit(500))
print(acc1.withdraw(2000))
print(acc2.deposit(100))

print(acc1.get_balance())

try:
    print(acc1.__balance)
except AttributeError:
    print("Direct access to balance is blocked by encapsulation.")