#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Expense {
private:
    string name;
    double amount;
    string category;

public:
    Expense(const string& name1, double amount1, const string& category1)
        : name(name1), amount(amount1), category(category1) {}

    string getName() const {
        return name;
    }

    double getAmount() const {
        return amount;
    }

    string getCategory() const {
        return category;
    }
};

class Budget {
private:
    string category;
    double limit;
    double spent;
    vector<Expense> expenseHistory;

public:
    Budget(const string& catg, double lim) {
        category = catg;
        limit = lim;
        spent = 0.0;
    }

    void addExpense(const Expense& expense) {
        spent += expense.getAmount();
        expenseHistory.push_back(expense);
    }

    double getRemainingBudget() const {
        return limit - spent;
    }

    string getCategory() const {
        return category;
    }

    double getSpent() const {
        return spent;
    }

    double getLimit() const {
        return limit;
    }

    const vector<Expense>& getExpenseHistory() const {
        return expenseHistory;
    }

    void modifyBudget(double newLimit) {
        limit = newLimit;
    }
};

class PersonalFinanceManager {
private:
    vector<Budget> budgets;

public:
    void addBudget(const Budget& budget) {
        budgets.push_back(budget);
    }

    void displayCategories() const {
        cout << "Available Budget Categories:\n";
        for (const auto& budget : budgets) {
            cout << "- " << budget.getCategory() << "\n";
        }
        cout << "\n";
    }

    void displayBudgets() const {
        for (const Budget& budget : budgets) {
            cout << "Category: " << budget.getCategory() << "\n";
            cout << "Limit: $" << budget.getLimit() << "\n";
            cout << "Spent: $" << budget.getSpent() << "\n";
            cout << "Remaining Budget: $" << budget.getRemainingBudget() << "\n\n";
        }
    }

    void addBudgetExpense(const string& category, const Expense& expense) {
        for (auto& budget : budgets) {
            if (budget.getCategory() == category) {
                budget.addExpense(expense);
                return;
            }
        }

        cout << "Category not found. Creating a new budget for category: " << category << "\n";
        addBudget(Budget(category, 0.0));
        addBudgetExpense(category, expense);
    }

    void modifyBudget(const string& category, double newLimit) {
        for (auto& budget : budgets) {
            if (budget.getCategory() == category) {
                budget.modifyBudget(newLimit);
                return;
            }
        }

        cout << "Category not found. Cannot modify budget.\n";
    }

    const vector<Budget>& getBudgets() const {
        return budgets;
    }
};

int main() {
    cout << "\n\n\n\n\n\n";
    cout << "            Welcome to the Personal Finance Manager App!\n";
    cout << "        This application helps you manage your budgets and expenses.\n";
    cout << "                -------------------------------------\n\n\n";
    PersonalFinanceManager manager;

    int choice;
    do {
        cout << "        Menu:\n\n";
        cout << "        1. Add Budget\n";
        cout << "        2. Add Expense\n";
        cout << "        3. Display Budgets\n";
        cout << "        4. Modify Budget\n";
        cout << "        5. Exit\n";
        cout << "        Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string category;
                double limit;
                cout << "Enter budget category: ";
                cin >> category;
                cout << "Enter budget limit: $";
                cin >> limit;
                manager.addBudget(Budget(category, limit));
                break;
            }
            case 2: {
                string category;
                string expenseName;
                double expenseAmount;

                cout << "Enter budget category to add expense: \n";
                manager.displayCategories();
                cout << "Enter your choice: ";
                cin >> category;

                cout << "Enter expense name: ";
                cin.ignore();
                getline(cin, expenseName);

                cout << "Enter expense amount: $";
                cin >> expenseAmount;

                manager.addBudgetExpense(category, Expense(expenseName, expenseAmount, category));
                break;
            }
            case 3:
                manager.displayBudgets();
                break;
            case 4: {
                string category;
                double newLimit;

                cout << "Enter budget category to modify: \n";
                manager.displayCategories();
                cout << "Enter your choice: ";
                cin >> category;

                cout << "Enter new budget limit: $";
                cin >> newLimit;

                manager.modifyBudget(category, newLimit);
                break;
            }
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
