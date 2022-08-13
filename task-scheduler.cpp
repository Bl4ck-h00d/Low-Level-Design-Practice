#include <bits/stdc++.h>

using namespace std;

enum TaskType
{
    STORY,
    FEATURE,
    BUG
};

enum TaskStatus
{
    OPEN,
    IN_PROGRESS,
    RESOLVED,
    DELAYED,
    COMPLETED
};

class Task;

class Sprint
{
    int begin, end;
    string name;
    vector<Task> tasks;
public:
    Sprint(int begin, int end, string name):begin(begin), end(end), name(name) {}
    vector<Task> getTasks() const;
    void addTask(Task &);
    void printDetails();
};

vector<Task> Sprint::getTasks() const {
    return tasks;
}

void Sprint::addTask(Task& task){
    tasks.push_back(task);
}

void Sprint::printDetails() {
    cout << "Sprint Name: " << name << endl;
    cout << "Spring Begins: " << begin << endl;
    cout << "Spring Ends: " << end << endl;
}

class Task{

    int id;
    string subtract;
    User user;
    TaskType taskType;
    TaskStatus taskStatus;
public:
    Task() {
        this->id = getUniqueId();
        this->taskStatus = TaskStatus::OPEN;
    }
    int getId() const;
    void setSubtract(const string &subtract);
    void setTaskStatus(TaskStatus status);
    void setTaskType(TaskType taskType);
    void setUser(User user);
private:
    int getUniqueId();
};

int Task::getUniqueId() {
    static int taskId = 1;
    return taskId++;
}

class User{
    vector<Task> taskList;
    vector<Sprint> sprintList;

public:
    Task createTask(TaskType);
    Task createTask(string); //func overloadig for story type
    Sprint createSprint(int, int, string);
    bool addToSprint(Sprint &, Task &);
    bool removeFromSprint(Sprint &, Task &);
    void printAllTasks();
    bool changeStatus(Task &, TaskStatus);
};

Task User::createTask(TaskType taskType)
{
    if (taskType == TaskType::STORY)
    {
        cout << "Warning! Task of type STORY is being created with no subtract." << endl;
    }
    Task task;
    task.setTaskType(taskType);
    task.setUser(*this);
    taskList.push_back(task);
    return task;
}

Task User::createTask(string subtract)
{
    Task task;
    task.setTaskType(TaskType::STORY);
    task.setSubtract(subtract);
    task.setUser(*this);
    taskList.push_back(task);
    return task;
}

Sprint User::createSprint(int begin, int end, string name){
    Sprint sprint(begin, end, name);
    sprintList.push_back(sprint);

    return sprint;
}

int main()
{

    cout << "Hello World!" << endl;
    return 0;
}