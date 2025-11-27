#include <bits/stdc++.h>
using namespace std;

struct Person {
    string name;
    string gender; 
    vector<Person*> parents;
    vector<Person*> children;

    Person(const string& n, const string& g) : name(n), gender(g) {}
};

class FamilyTree {
private:
    unordered_map<string, Person*> people;

public:
    ~FamilyTree() {
        for (auto& pair : people) {
            delete pair.second;
        }
    }

    void addPerson(const string& name, const string& gender) {
        if (people.find(name) == people.end()) {
            people[name] = new Person(name, gender);
        }
    }

    void addParentChild(const string& parentName, const string& parentGender,
                        const string& childName, const string& childGender) {
        addPerson(parentName, parentGender);
        addPerson(childName, childGender);
        Person* parent = people[parentName];
        Person* child = people[childName];
        parent->children.push_back(child);
        child->parents.push_back(parent);
    }

    vector<string> getParents(const string& name) {
        vector<string> result;
        if (people.find(name) != people.end()) {
            for (auto& p : people[name]->parents) {
                result.push_back(p->name);
            }
        }
        return result;
    }

    vector<string> getFather(const string& name) {
        vector<string> fathers;
        if (people.find(name) != people.end()) {
            for (auto& p : people[name]->parents) {
                if (p->gender == "male") {
                    fathers.push_back(p->name);
                }
            }
        }
        return fathers;
    }

    vector<string> getGrandmother(const string& name) {
        unordered_set<string> grandmothers;
        auto parents = getParents(name);
        for (const auto& parent : parents) {
            auto gps = getParents(parent);
            for (const auto& gp : gps) {
                if (people[gp]->gender == "female") {
                    grandmothers.insert(gp);
                }
            }
        }
        return {grandmothers.begin(), grandmothers.end()};
    }

    bool parseQuery(const string& query, string& relationship, string& person) {
        regex pattern(R"((\w+)\s+of\s+(\w+))");
        smatch matches;
        string lowerQuery = query;
        transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

        if (regex_match(lowerQuery, matches, pattern)) {
            relationship = matches[1].str();
            person = matches[2].str();

            if (!person.empty()) person[0] = toupper(person[0]);
            return true;
        }
        return false;
    }

    void queryRelationship(const string& query) {
        string relationship, person;
        if (!parseQuery(query, relationship, person)) {
            cout << "Invalid query format. Use 'father of kate'\n";
            return;
        }

        vector<string> results;
        if (relationship == "father") {
            results = getFather(person);
        } else if (relationship == "grandmother") {
            results = getGrandmother(person);
        } else {
            cout << "Unsupported relationship: " << relationship << "\n";
            return;
        }

        if (results.empty()) {
            results.push_back("No " + relationship + " found");
        }

        string resultStr = "\n";
        resultStr += "            " + relationship.substr(0,1) + relationship.substr(1) + " of " + person + "\n";
        resultStr += "--------------------------------------------------\n";
        for (const auto& res : results) {
            resultStr += "| " + res + string(50 - res.length(), ' ') + "|\n";
        }
        resultStr += "--------------------------------------------------\n";

        cout << resultStr;
    }
};

int main() {
    FamilyTree tree;

    // Sample tree
    tree.addParentChild("John", "male", "Bob", "male");
    tree.addParentChild("Mary", "female", "Bob", "male");
    tree.addParentChild("Bob", "male", "Kate", "female");
    tree.addParentChild("Alice", "female", "Kate", "female");
    tree.addParentChild("Bob", "male", "Frank", "male");
    tree.addParentChild("Alice", "female", "Frank", "male");

    char choice;

    do {
        string query;
        cout << "Enter query (e.g., 'father of kate'): ";
        getline(cin, query);

        tree.queryRelationship(query);

        cout << "Do u wanna continue? (y/n): ";
        cin >> choice;
        cin.ignore(); // clear input buffer

    } while(choice == 'y' || choice == 'Y');

    return 0;
}
