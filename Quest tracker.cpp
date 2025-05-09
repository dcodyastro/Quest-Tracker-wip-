#include <iostream>
#include <vector>
#include <string>
using namespace std;

//enum represents Quest status
enum class QuestStatus {
    NotStarted,
    InProgress,
    Completed,
    Failed,
};

class Quest {
private:
    string id; // a custom identifier for quest
    string description; // another custom identifier for the quest
    QuestStatus status; // shows the current status of the quest
public:
    Quest(const string id, const string description)
        : id(id), description(description), status(QuestStatus::NotStarted) {} // sets default status to not started

    void updateStatus(QuestStatus newStatus) { // updates the quest status to the new status
        status = newStatus;
    }

    string getId() const { return id; }
    string getDescription() const { return description; }
    QuestStatus getStatus() const { return status; }

    void display() const {
        cout << "Quest ID: " << id << ", Description: " << description
             << ", Status: " << (status == QuestStatus::NotStarted ? "Not Started" :
                                 status == QuestStatus::InProgress ? "In Progress" :
                                 status == QuestStatus::Completed ? "Completed" : "Failed")
             << endl;
    }
};

class QuestBoard {
private:
    vector<Quest> quests;
public:
    void addQuest(const Quest& quest) {
        quests.push_back(quest);
    }

    void displayQuests() const {
        cout << "Available Quests:" << endl;
        for (const auto& quest : quests) {
            quest.display();
        }
    }

    Quest* acceptQuest(const string& questId) {
        for (auto& quest : quests) {
            if (quest.getId() == questId) {
                quest.updateStatus(QuestStatus::InProgress);
                return &quest;
            }
        }
        return nullptr;
    }
};

int main() {
    // Create a main quest
    Quest mainQuest("main_001", "Defeat the dragon and save the kingdom");
    mainQuest.updateStatus(QuestStatus::InProgress);

    // Create a quest board
    QuestBoard questBoard;
    questBoard.addQuest(Quest("side_001", "Collect 10 herbs for the healer"));
    questBoard.addQuest(Quest("side_002", "Help the farmer defend his crops"));

    // Display quests
    cout << "Main Quest:" << endl;
    mainQuest.display();

    cout << endl;
    questBoard.displayQuests();

    // Accept a quest
    cout << endl << "Accepting quest 'side_001'..." << endl;
    Quest* acceptedQuest = questBoard.acceptQuest("side_001");
    if (acceptedQuest) {
        cout << "Quest accepted:" << endl;
        acceptedQuest->display();
    } else {
        cout << "Quest not found!" << endl;
    }

    return 0;
}
